#ifndef LAB_14_LINQ_CPP
#define LAB_14_LINQ_CPP

#include <iterator>
#include <vector>
#include <functional>
#include <iostream>

namespace linq {
    namespace impl {
        template<class T>
        struct take_enumerator;

        template<class T>
        struct drop_enumerator;

        template<class T, class U, class F>
        struct select_enumerator;

        template<class T, class F>
        struct until_enumerator;

        template<class T, class F>
        struct where_enumerator;

        template<class T>
        struct enumerator {
            enumerator(const enumerator &) = delete;

            enumerator &operator=(const enumerator &) = delete;

            enumerator &operator=(enumerator &&) = default;

            enumerator() = default;

            virtual ~enumerator() = default;

            virtual operator bool() const = 0;

            virtual T &operator*() = 0;

            virtual enumerator &operator++() = 0;

        public:
            auto take(int number) {
                return take_enumerator(*this, number);
            }

            auto drop(int number) {
                return drop_enumerator(*this, number);
            }

            template<class U = T, class F>
            auto select(F &func) {
                return select_enumerator<U, T, F>(*this, func);
            }

            template<class U = T, class F>
            auto select(F &&func) {
                return select_enumerator<U, T, F>(*this, std::move(func));
            }

            template<class F>
            auto until(F &func) {
                return until_enumerator<T, F>(*this, func);
            }

            template<class F>
            auto until(F &&func) {
                return until_enumerator<T, F>(*this, std::move(func));
            }

            auto until_eq(T value) {
                return until_enumerator<T, std::function<bool(T)>>(*this, value);
            }

            template<class F>
            auto where(F &func) {
                return where_enumerator(*this, func);
            }

            template<class F>
            auto where(F func) {
                return where_enumerator(*this, std::move(func));
            }

            auto where_neq(T value) {
                return where_enumerator<T, std::function<bool(T)>>(*this, value);
            }

            auto to_vector() {
                enumerator &self = *this;
                std::vector<T> res;
                while (self) {
                    res.push_back(*self);
                    ++self;
                }
                return res;
            }

            template<class Iter>
            void copy_to(Iter it) {
                enumerator &self = *this;
                while (self) {
                    *it = *self;
                    ++it;
                    ++self;
                }
            }
        };

        template<class Iter>
        struct range_enumerator : public enumerator<typename std::iterator_traits<Iter>::value_type> {
            range_enumerator(Iter beg, Iter end) : beg(beg), end(end) {}

            using value_type = typename std::iterator_traits<Iter>::value_type;

            virtual operator bool() const override {
                return beg != end;
            }

            virtual value_type &operator*() {
                return const_cast<value_type &>(*beg);
            }

            virtual enumerator<value_type> &operator++() override {
                beg++;
                return *this;
            }

        private:
            Iter beg, end;
        };

        template<class T>
        struct take_enumerator : public enumerator<T> {
            take_enumerator(enumerator<T> &parent, int number) : parent(parent), number(number) {}

            virtual operator bool() const override {
                return number && parent;
            }

            virtual T &operator*() {
                return *parent;
            }

            virtual enumerator<T> &operator++() override {
                number--;
                ++parent;
                return *this;
            }

        private:
            enumerator<T> &parent;
            int number;
        };

        template<class T>
        struct drop_enumerator : public enumerator<T> {
            drop_enumerator(enumerator<T> &parent, int number) : parent(parent), number(number) {
                while (number > 0 && parent) {
                    number--;
                    ++parent;
                }
            }

            virtual operator bool() const override {
                return parent;
            }

            virtual T &operator*() {
                return *parent;
            }

            virtual enumerator<T> &operator++() override {
                ++parent;
                return *this;
            }

        private:
            enumerator<T> &parent;
            int number;
        };

        template<class T, class U, class F>
        struct select_enumerator : public enumerator<T> {
            select_enumerator(enumerator<U> &parent, F &func_) : parent(parent),
                                                                 func(func_) {}

            select_enumerator(enumerator<U> &parent, F &&func_) : parent(parent),
                                                                  func(func_) {}

            virtual operator bool() const override {
                return parent;
            }

            virtual T &operator*() override {
                last_created = func(*parent);
                return last_created;
            }

            virtual enumerator<T> &operator++() override {
                ++parent;
                return *this;
            }

        private:
            enumerator<U> &parent;
            const F &func;
            T last_created;
        };

        template<class T, class F>
        struct until_enumerator : public enumerator<T> {
            until_enumerator(enumerator<T> &parent, F &func_) : parent(parent), func(func_) {}

            until_enumerator(enumerator<T> &parent, F &&func_) : parent(parent), func(func_) {}

            until_enumerator(enumerator<T> &parent, T val) : parent(parent), compared(std::move(val)), isCompared(true), func(nullptr) {}

            virtual operator bool() const override {
                return parent && !predicate_result(*parent);
            }

            virtual T &operator*() override {
                return *parent;
            }

            virtual enumerator<T> &operator++() override {
                ++parent;
                return *this;
            }

            bool predicate_result(T &val) const {
                return !isCompared ? func(val) : val == compared;
            }

        private:
            enumerator<T> &parent;
            T compared;
            bool isCompared = false;
            const F &func;
        };

        template<class T, class F>
        struct where_enumerator : public enumerator<T> {
            void shift() {
                while (parent && !predicate_result(*parent)) {
                    ++parent;
                }
            }

            bool predicate_result(T &val) {
                return !isCompared ? func(val) : val != compared;
            }

            where_enumerator(enumerator<T> &parent, T value) : parent(parent), compared(std::move(value)), isCompared(true), func(nullptr) {
                shift();
            }

            where_enumerator(enumerator<T> &parent, F &func_) : parent(parent), func(func_) {
                shift();
            }

            where_enumerator(enumerator<T> &parent, F &&func_) : parent(parent), func(func_) {
                shift();
            }

            virtual operator bool() const override {
                return parent;
            }

            virtual T &operator*() override {
                return *parent;
            }

            virtual enumerator<T> &operator++() override {
                ++parent;
                shift();
                return *this;
            }

        private:
            enumerator<T> &parent;
            T compared;
            bool isCompared = false;
            const F &func;
        };
    }

    template<class Iter>
    auto from(Iter beg, Iter end) {
        return linq::impl::range_enumerator(beg, end);
    }
}


#endif //LAB_14_LINQ_CPP
