#pragma once
#include <memory>
#include <functional>
#include "shared_factory.h"


namespace t2k {

    //class link_linear : public std::enable_shared_from_this<link_linear> {
    class link_linear : public t2k::SharedFactory<link_linear> {
    public:
        using weak = std::weak_ptr<link_linear>;
        using shared = std::shared_ptr<link_linear>;

    protected:
        link_linear() {}

    private:
        weak prev_;
        shared next_ = nullptr;

    public:
        virtual ~link_linear() {}

        inline shared getNext() const noexcept {
            return next_;
        }
        inline shared getPrev() const noexcept {
            return prev_.lock();
        }
        inline shared getFront() noexcept {
            shared front = shared_from_this();
            while (front->getPrev()) {
                front = front->getPrev();
            }
            return front;
        }
        inline shared getBack() noexcept {
            shared back = shared_from_this();
            while (back->next_) {
                back = back->next_;
            }
            return back;
        }
        inline shared pop() noexcept {
            shared prev = getPrev();
            shared next = getNext();
            if (next) next->prev_ = prev;
            if (prev) prev->next_ = next;
            return next;
        }

        inline void pushBack(const shared& add) noexcept {
            shared last = getBack();
            last->next_ = add;
            add->prev_ = last;
        }

		inline uint32_t getSize() {
			shared obj = getFront();
			for (uint32_t i = 1; ; ++i) {
				obj = obj->getNext();
				if (!obj) return i;
			}
		}

        shared find(const std::function<bool(shared)>& comp) noexcept {
            shared check = getFront();
            while (check) {
                if (comp(check)) return check;
                check = getNext();
            }
            return nullptr;
        }
    };

}