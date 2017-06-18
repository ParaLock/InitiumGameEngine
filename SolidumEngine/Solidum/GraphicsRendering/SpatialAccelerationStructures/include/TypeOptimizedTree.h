#pragma once
#include "../../../sysInclude.h"

template<typename T, typename E_TYPE>
class TypeOptimizedTree
{
private:
	struct RootNode {
		E_TYPE _type;

		std::list<std::shared_ptr<T>> _childNodes;
	};

	std::list<RootNode> _rootLists;
public:
	TypeOptimizedTree() {};
	~TypeOptimizedTree() {};

	void addNode(std::shared_ptr<T> node) {

		if (_rootLists.empty()) {

			RootNode newRootNode;

			newRootNode._type = node->getType();

			newRootNode._childNodes.push_back(node);

			_rootLists.push_back(newRootNode);

			return;
		}
		else {

			auto& itr = _rootLists.begin();

			while (itr != _rootLists.end()) {

				RootNode& rootNode = *itr;

				if (rootNode._type == node->getType()) {

					rootNode._childNodes.push_back(node);

					return;
				}

				itr++;
			}

			RootNode rootNode;

			rootNode._type = node->getType();

			rootNode._childNodes.push_back(node);

			_rootLists.push_back(rootNode);
		}
	}

	void removeNode(std::shared_ptr<T> node) {
		
		auto& itr = _rootLists.begin();

		while (itr != _rootLists.end()) {

			RootNode& rootNode = *itr;

			if (rootNode._type == node->getType()) {
				
				auto& innerItr = rootNode._childNodes.begin();

				while (innerItr != rootNode._childNodes.end()) {

					if (*innerItr == node) {

						rootNode._childNodes.erase(innerItr);

						return;
					}

					innerItr++;
				}
			}

			itr++;
		}

	}

	void queryNodesByType(E_TYPE e, std::list<std::shared_ptr<T>>& outList) {

		auto& itr = _rootLists.begin();

		while (itr != _rootLists.end()) {

			RootNode& rootNode = *itr;

			if (rootNode._type == e) {

				auto& innerItr = rootNode._childNodes.begin();

				while (innerItr != rootNode._childNodes.end()) {

					outList.push_back(*innerItr);

					innerItr++;
				}
			}

			itr++;
		}
	}

	void queryAllNodes(std::list<std::shared_ptr<T>>& out) {

		for each(RootNode root in _rootLists) {
			for each(std::shared_ptr<T> node in root._childNodes) {
				out.push_back(node);
			}
		}
	}
};

