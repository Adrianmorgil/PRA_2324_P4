#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
	int nelem;
	BSNode<T> *root;

	T search(BSNode<T>* n, T e) const{
		if(n == nullptr){
			throw std::runtime_error("elemento no encontrado");
		}else if(n->elem < e){
			return search(n->right, e);
		}else if(n->elem > e){
			return search(n->left, e);
		}else{
			return e;
		}
	}
	BSNode<T>* insert(BSNode<T>* n, T e){
		if(n == nullptr){
			return new BSNode<T>(e);
		}else if(n->elem == e){
			throw std::runtime_error("el elemento ya se encuentra en el arbol");
		}else if(n->elem < e){
			n->right = insert(n->right, e);
		}else if(n->elem > e){
			n->left = insert(n->left, e);
		}
		return n;
	}

	void print_inorder(std::ostream &out, BSNode<T>* n) const{
		if(n != nullptr){
			print_inorder(out, n->left);
			out << n->elem << " ";

			if( n->right != nullptr){
				print_inorder(out, n->right);
		
			}
		}
	}
	BSNode<T>* remove(BSNode<T>* n, T e){
		if(n == nullptr){
			throw std::runtime_error("Element not found!");
		}
		else if(n->elem < e){
			n->right = remove(n->right, e);
		}
		else if(n->elem > e){
			n->left = remove(n->left, e);
		}
		else{
			if(n->left != nullptr && n->right != nullptr){
				n->elem = max(n->left);
				n->left = remove_max(n->left);
			} else {
				n = (n->left != nullptr)? n->left: n->right;
			}
		}
		return n;
	}

	T max(BSNode<T>* n) const{
		if(n == nullptr){
			throw std::runtime_error("Element not found!");	
		}
		else if(n->right != nullptr){
			return max(n->right);
		}
		else{
			return n->elem;
		}		
	}
			
	BSNode<T>* remove_max(BSNode<T>* n){
		BSNode<T>* ret;

		if (n->right == nullptr){
			ret = n->left;
			delete n;
		}
		else{
			n->right = remove_max(n->right);	
			ret = n;
		}
		return ret;
	}

	void delete_cascade(BSNode<T>* n){
		while(n!=nullptr){
			n = remove(n, n->elem);
		}	
	}

    public:
	BSTree(){
		root = nullptr;
	}
	int size() const{
		return nelem;
	}
	T search(T e) const{
		return search(root, e); 
	}
	T operator[](T e) const{
		return search(e);
	}
	void insert(T e){
		root = insert(root, e);
		nelem ++;
	}
	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		bst.print_inorder(out, bst.root);
		return out;
	}
	void remove(T e){
		root = remove(root, e);
		nelem --;
	}
	~BSTree(){
		delete_cascade(root);
		nelem = 0;
	}
    
};

#endif
