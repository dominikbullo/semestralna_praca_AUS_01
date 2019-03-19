#pragma once

#include "tree.h"
#include "../list/list.h"
#include "../list/array_list.h"

namespace structures
{
	/// <summary> Vrchol viaccestneho stromu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo vrchole stromu. </typepram>
	template <typename T>
	class MultiWayTreeNode : public TreeNode<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		MultiWayTreeNode(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Vrchol viaccestneho stromu, z ktoreho sa prevezmu vlastnosti. </param>
		/// <remarks> Vytvori sa ako plytka kopia vrcholu other. </remarks>
		MultiWayTreeNode(const MultiWayTreeNode<T>& other);

		/// <summary> Destruktor. </summary>
		~MultiWayTreeNode();

		/// <summary> Vytvori plytku kopiu vrchola (teda skopiruje iba data a smerniky na synov). </summary>
		/// <returns> Vystvorena plytka kopia vrcholu. </returns>
		TreeNode<T>* shallowCopy() override;

		/// <summary> Test, ci je list. </summary>
		/// <returns> true, ak je list, false inak. </returns>
		bool isLeaf() override;

		/// <summary> Spristupni syna vrcholu podla jeho pozicie v tomto vrchole. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Syn vrcholu. </returns>
		TreeNode<T>* getSon(int order) const override;

		/// <summary> Vlozi noveho syna vrcholu na dane miesto. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		void insertSon(TreeNode<T>* son, int order) override;

		/// <summary> Nahradi syna vrcholu na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je poradie neplatne. </exception>
		/// <returns> Nahradeny syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		TreeNode<T>* replaceSon(TreeNode<T>* son, int order) override;

		/// <summary> Odstrani syna na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Odstraneny syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		TreeNode<T>* removeSon(int order) override;

		/// <summary> Vrati pocet synov vrcholu. </summary>
		/// <returns> Vzdy K. </returns>
		int degree() override;
	protected:
		/// <summary> Synova vrchola. </summary>
		List<MultiWayTreeNode<T>*>* children_;
	};

	/// <summary> Viaccestny strom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strome. </typepram>
	template <typename T>
	class MultiWayTree : public Tree<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		MultiWayTree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Viaccestny strom, z ktoreho sa prevezmu vlastnosti. </param>
		MultiWayTree(const MultiWayTree<T>& other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vytvori a vrati instanciu vrcholu k-cestneho stromu. </summary>
		/// <returns> Vytvorena instancia vrcholu k-cestneho stromu. </returns>
		TreeNode<T>* createTreeNodeInstance() override;
	};


	template<typename T>
	inline MultiWayTreeNode<T>::MultiWayTreeNode(T data) :
		TreeNode<T>(data),
		children_(new ArrayList<MultiWayTreeNode<T>*>())
	{
	}

	template<typename T>
	inline MultiWayTreeNode<T>::MultiWayTreeNode(const MultiWayTreeNode<T>& other) :
		TreeNode<T>(other),
		children_(dynamic_cast<ArrayList<MultiWayTreeNode<T>*>*>(other.children_->clone()))
	{
	}

	template<typename T>
	inline MultiWayTreeNode<T>::~MultiWayTreeNode()
	{
		// TODO 08: MultiWayTreeNode<T>
	}

	template<typename T>
	inline TreeNode<T>* MultiWayTreeNode<T>::shallowCopy()
	{
		// TODO 08: MultiWayTreeNode<T>
		throw std::exception("MultiWayTreeNode<T>::shallowCopy: Not implemented yet.");
	}

	template<typename T>
	inline bool MultiWayTreeNode<T>::isLeaf()
	{
		// TODO 08: MultiWayTreeNode<T>
		throw std::exception("MultiWayTreeNode<T>::isLeaf: Not implemented yet.");
	}

	template<typename T>
	inline TreeNode<T>* MultiWayTreeNode<T>::getSon(int order) const
	{
		// TODO 08: MultiWayTreeNode<T>
		throw std::exception("MultiWayTreeNode<T>::getSon: Not implemented yet.");
	}

	template<typename T>
	inline void MultiWayTreeNode<T>::insertSon(TreeNode<T>* son, int order)
	{
		// TODO 08: MultiWayTreeNode<T>
		throw std::exception("MultiWayTreeNode<T>::insertSon: Not implemented yet.");
	}

	template<typename T>
	inline TreeNode<T>* MultiWayTreeNode<T>::replaceSon(TreeNode<T>* son, int order)
	{
		// TODO 08: MultiWayTreeNode<T>
		throw std::exception("MultiWayTreeNode<T>::replaceSon: Not implemented yet.");
	}

	template<typename T>
	inline TreeNode<T>* MultiWayTreeNode<T>::removeSon(int order)
	{
		// TODO 08: MultiWayTreeNode<T>
		throw std::exception("MultiWayTreeNode<T>::removeSon: Not implemented yet.");
	}

	template<typename T>
	inline int MultiWayTreeNode<T>::degree()
	{
		// TODO 08: MultiWayTreeNode<T>
		throw std::exception("MultiWayTreeNode<T>::degree: Not implemented yet.");
	}

	template<typename T>
	inline MultiWayTree<T>::MultiWayTree() :
		Tree<T>()
	{
	}

	template<typename T>
	inline MultiWayTree<T>::MultiWayTree(const MultiWayTree<T>& other) :
		Tree<T>(other)
	{
	}

	template<typename T>
	inline Structure * MultiWayTree<T>::clone() const
	{
		return new MultiWayTree<T>(*this);
	}

	template<typename T>
	inline TreeNode<T>* MultiWayTree<T>::createTreeNodeInstance()
	{
		T data = T();
		return new MultiWayTreeNode<T>(data);
	}

}

