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

	std::list<std::shared_ptr<T>> queryNodesByType(E_TYPE e) {

		auto& itr = _rootLists.begin();

		std::list<std::shared_ptr<T>> _discoveredNodes;

		while (itr != _rootLists.end()) {

			RootNode& rootNode = *itr;

			if (rootNode._type == e) {

				auto& innerItr = rootNode._childNodes.begin();

				while (innerItr != rootNode._childNodes.end()) {

					_discoveredNodes.push_back(*innerItr);

					innerItr++;
				}

				return _discoveredNodes;
			}

			itr++;
		}

		return std::list<std::shared_ptr<T>>();

	}
};

