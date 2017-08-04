#pragma once
#include "../../../sysInclude.h"

template<typename T, typename E_TYPE>
class TypeOptimizedTree
{
private:
	struct RootNode {
		E_TYPE _type;

		std::list<T> _childNodes;
	};

	std::list<RootNode> _rootLists;
public:
	TypeOptimizedTree() {};
	~TypeOptimizedTree() {};

	void addNode(T node) {

		E_TYPE type;

		if (std::is_pointer<T>::value) {
			type = node->getType();

		}
		else {
			type = node->getType();
		}

		if (_rootLists.empty()) {

			RootNode newRootNode;

			newRootNode._childNodes.push_back(node);
			newRootNode._type = type;

			_rootLists.push_back(newRootNode);

			return;
		}
		else {

			auto& itr = _rootLists.begin();

			while (itr != _rootLists.end()) {

				RootNode& rootNode = *itr;

				if (rootNode._type == type) {

					rootNode._childNodes.push_back(node);

					return;
				}

				itr++;
			}

			RootNode rootNode;

			rootNode._type = type;

			rootNode._childNodes.push_back(node);

			_rootLists.push_back(rootNode);
		}
	}

	void removeNode(T node) {
		
		E_TYPE type;

		if (std::is_pointer<T>::value) {
			type = node->getType();

		}
		else {
			type = node->getType();
		}

		auto& itr = _rootLists.begin();

		while (itr != _rootLists.end()) {

			RootNode& rootNode = *itr;

			if (rootNode._type == type) {
				
				auto& innerItr = rootNode._childNodes.begin();

				while (innerItr != rootNode._childNodes.end()) {

					T innerItrVal = *innerItr;

					if (innerItrVal == node) {

						rootNode._childNodes.erase(innerItr);

						return;
					}

					innerItr++;
				}
			}

			itr++;
		}

	}

	void queryNodesByType(E_TYPE e, std::list<T>& outList) {

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

	void queryAllNodes(std::list<T>& out) {

		for each(RootNode root in _rootLists) {
			for each(T node in root._childNodes) {
				out.push_back(node);
			}
		}
	}
};

