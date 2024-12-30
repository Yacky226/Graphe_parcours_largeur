#pragma once
#include <list>
#include <iostream>
#include <queue>
#include<set>
// Structure g�n�rique pour repr�senter un n�ud de graphe
template<typename T>
struct Node {
	T data; // Valeur du n�ud
   std::string couleur;
	int distance;
    std::list<Node<T>*> successeurs; // Liste des successeurs

    // Constructeur pour initialiser un n�ud
    Node(T value) : data(value),couleur("blanc"),distance(INT_MAX) {}
};

// Classe pour repr�senter un graphe
template<typename T>
class Graph
{
private:
    Node<T>* root; // Racine du graphe
    void deleteGraph(Node<T>* node, std::set<Node<T>*>& visited); // M�thode r�cursive pour lib�rer la m�moire

public:
    Graph(T value);                       // Constructeur
    Node<T>* search(T parent);            // Recherche d'un n�ud par valeur
    void insert(T parent, T fils);        // Ajout d'une ar�te entre parent et fils
	void parcours_largeur(); // Parcours en largeur
    ~Graph();                             // Destructeur pour nettoyer la m�moire
};

// Constructeur
template<typename T>
inline Graph<T>::Graph(T value)
{
    root = new Node<T>(value);
}

// M�thode pour rechercher un n�ud par sa valeur
template<typename T>
inline Node<T>* Graph<T>::search(T parent)
{
    if (!root) return nullptr;
    //une queue pour parcourir le graphe en largeur
    std::queue<Node<T>*> TempQ;
    //Sert � marquer les noeuds visit�s Pour �viter les boucles infinies dans les graphes cycliques 
    std::set<Node<T>*> visited;

    TempQ.push(root);
    while (!TempQ.empty())
    {
        Node<T>* current = TempQ.front();
        TempQ.pop();

        // V�rifie si le n�ud courant contient la valeur recherch�e
        if (current->data == parent)
        {
            return current;
        }

        // Ajoute les successeurs non visit�s � la file
        for (Node<T>* fils : current->successeurs)
        {
            if (visited.find(fils) == visited.end())
            {
                TempQ.push(fils);
                visited.insert(fils);
            }
        }
    }
    return nullptr;
}

// M�thode pour ins�rer une ar�te dans le graphe
template<typename T>
inline void Graph<T>::insert(T parent, T fils)
{
    Node<T>* P = search(parent);
    if (!P)
    {
        std::cout << "Parent " << parent << " inexistant dans le graphe" << std::endl;
        return;
    }

    // V�rifie si le fils existe d�j�
    Node<T>* f = search(fils);
    if (!f)
    {
        f = new Node<T>(fils);
    }

    // V�rifie si le fils est d�j� un successeur du parent
    for (Node<T>* successeur : P->successeurs)
    {
        if (successeur == f)
        {
            std::cout << "Lien deja existant entre " << parent << " et " << fils << std::endl;
            return;
        }
    }

    // Ajoute le lien entre le parent et le fils
    P->successeurs.push_back(f);
}



template<typename T>
inline void Graph<T>::parcours_largeur()
{
    if (!root) return;

	int nb = 1;//compteur d'it�ration
	std::queue<Node<T>*> TempQ;//une queue pour parcourir le graphe en largeur
	TempQ.push(root);//Ajoute la racine � la file

	root->couleur = "gris";//Marque la racine comme visit�e
	root->distance = 0;//distance de la racine � elle-m�me est 0

    while (!TempQ.empty())
    {
		Node<T>* current = TempQ.front();//R�cup�re le n�ud en t�te de la file
		TempQ.pop();//Supprime le n�ud en t�te de la file
		std::cout << "Noeudpere: "  << current->data 
            << " distance: " << current->distance 
            <<" couleur " << current->couleur << std::endl;
		// Ajoute les successeurs du noeud courrant non visit�s � la file
        for (Node<T>* fils : current->successeurs)
        {
			if (fils->couleur == "blanc")//Si le fils n'est pas visit�
            {
				fils->couleur = "gris";//Marque le fils comme visit�
				fils->distance = current->distance + 1;//Calcule la distance du fils par rapport � la racine
           std::cout << "Noeudfils: " << fils->data 
               << " distance: " << fils->distance 
               << " couleur " << fils->couleur << std::endl;
		   TempQ.push(fils);//Ajoute le fils � la file
            }
        }

		current->couleur = "noir";//Marque le n�ud courant comme trait� , le noeud n'a plus de fils � traiter
        std::cout << "Noeudtraiterfini: " << current->data 
            << " distance: " << current->distance 
            << " couleur " << current->couleur << std::endl;
		std::cout << "-------------- fin de Iteration"<<nb<<"------------------" << std::endl;
		nb++;
    }
}

// M�thode r�cursive pour lib�rer la m�moire
template<typename T>
void Graph<T>::deleteGraph(Node<T>* node, std::set<Node<T>*>& visited)
{
    if (!node || visited.find(node) != visited.end()) return;

    visited.insert(node);

    // Supprime les successeurs r�cursivement
    for (Node<T>* fils : node->successeurs)
    {
        deleteGraph(fils, visited);
    }

    delete node;
}

// Destructeur
template<typename T>
inline Graph<T>::~Graph()
{
    std::set<Node<T>*> visited; // Pour �viter les cycles dans les graphes
    deleteGraph(root, visited);
}
