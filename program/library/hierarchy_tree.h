#pragma once
#include <functional>
#include <memory>
#include "link_linear.h"


namespace t2k {

	class hierarchy_tree : public link_linear {
	public:
		using weak = std::weak_ptr< hierarchy_tree >;
		using shared = std::shared_ptr< hierarchy_tree >;

	protected:
		hierarchy_tree() {}

	private:
		weak parent_;
		shared child_ = nullptr;
		inline shared sharedFromThis() { return std::static_pointer_cast<hierarchy_tree>(shared_from_this()); }

	public:
		virtual ~hierarchy_tree() {}

		//----------------------------------------------------------------------------
		// ���̎擾
		inline shared getRoot() noexcept {
			if (!getParent()) return sharedFromThis();
			return getParent()->getRoot();
		}

		//----------------------------------------------------------------------------
		// �e�̎擾
		inline shared getParent() noexcept { return parent_.lock(); }

		//----------------------------------------------------------------------------
		// ���̃��\�b�h���Ăяo�����C���X�^���X���e���Ƃ��ā@�擪�f�[�^���擾
		inline shared getChild() noexcept { return child_; }

		//----------------------------------------------------------------------------
		// ���̃��\�b�h���Ăяo�����C���X�^���X���q���Ƃ��ā@�O�̎q���擾
		inline shared getPrev() noexcept { return std::static_pointer_cast<hierarchy_tree>(link_linear::getPrev()); }

		//----------------------------------------------------------------------------
		// ���̃��\�b�h���Ăяo�����C���X�^���X���q���Ƃ��ā@���̎q���擾
		inline shared getNext() noexcept { return std::static_pointer_cast<hierarchy_tree>(link_linear::getNext()); }

		//----------------------------------------------------------------------------
		// ���̃��\�b�h���Ăяo�����C���X�^���X���q���Ƃ��ā@�q�̐擪���擾
		inline shared getFront() noexcept {
			if (!getParent()) return sharedFromThis();
			return getParent()->child_;
		}

		//----------------------------------------------------------------------------
		// ���̃��\�b�h���Ăяo�����C���X�^���X���q���Ƃ��ā@�q�̍Ō�ɒǉ�
		inline void pushBack(const shared& add) {
			if (!getParent()) return;
			shared ptr = find([&](auto node) { return (node == add) ? true : false; });
			if (ptr == add) return;
			add->parent_ = parent_;
			link_linear::pushBack(add);
		}

		//----------------------------------------------------------------------------
		// ���̃��\�b�h���Ăяo�����C���X�^���X���e���Ƃ��ā@�q�̒ǉ�
		virtual inline bool pushChild(shared add) {
			if (add->parent_.lock()) return false;
			shared ptr = find([&](auto node) { return (node == add) ? true : false; });
			if (ptr == add) return false ;
			add->parent_ = sharedFromThis();
			if (child_) {
				child_->link_linear::pushBack(add);
				return true;
			}
			child_ = add;
			return true;
		}

		//--------------------------------------------------------------------------------------
		// ���̃��\�b�h���Ăяo�����C���X�^���X���q���Ƃ��ā@�����Ǝ����̎q���K�w�\�����痣�E
		virtual inline void pop() {
			shared parent = parent_.lock();
			if (!parent) return;
			if (!getPrev()) {
				parent->child_ = getNext();
			}
			link_linear::pop();
			parent_.reset();
		}

		//----------------------------------------------------------------------------
		// ���̃��\�b�h���Ăяo�����m�[�h�̊K�w�̐[�����擾( root �� 0 )
		inline int getDepth() {
			shared check = sharedFromThis();
			for (int i = 0; ; ++i) {
				check = check->getParent();
				if (!check) return i;
			}
		}

		//--------------------------------------------------------------------------------------
		// ���̃��\�b�h���Ăяo�����m�[�h�ȍ~�ɑ΂��ă��[�U�[��`�̏��������s����
		// ���[�U�[��`�֐����� pop �������s��Ȃ�����
		inline void roundup(const std::function<void(shared)>& call, bool is_call = true) {
			shared node = sharedFromThis();
			if (is_call) call(node);
			if (node->getChild()) node->getChild()->roundup(call, true);
			if (node->getNext()) node->getNext()->roundup(call, true);
			return;
		}

		//----------------------------------------------------------------------------
		// ���[�U�[��`�̔�r�֐��Ńc���[������
		// ���[�U�[��`�֐����� pop �������s��Ȃ�����
		shared find(const std::function<bool(shared)>& comp) noexcept {
			shared out = nullptr;
			getRoot()->roundup([&](auto node) { if (comp(node)) { out = node; } });
			return out;
		}

	};

}
