#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
 
 class Auteur{
	private:
		string nom_;
		bool prix_;
	public:
		Auteur(string nom):nom_(nom), prix_(false){}
		Auteur(string nom, bool prix):nom_(nom), prix_(prix){}
		string getNom() const{
			return nom_;
		}
		bool getPrix() const{
			return prix_;
		}
		Auteur(Auteur const &auteur)=delete;
 };
 
 class Oeuvre{
	private:
		string titre_;
		Auteur const &auteur_;
		string langage_;
	public:
		Oeuvre(string titre, Auteur const &auteur, string langage)
		:titre_(titre), auteur_(auteur), langage_(langage){}
		string getTitre() const{
			return titre_;
		} 
		Auteur const& getAuteur() const{
			return auteur_;
		}
		string getLangue() const{
			return langage_;
		}
		void affiche() const{
			cout<<titre_<<", "<<auteur_.getNom()<<", en "<<langage_<<endl;
		}
		~Oeuvre(){
			cout<<"L’oeuvre \""<<titre_<<", "<< auteur_.getNom()<<
			", en "<<langage_<<"\" n'est plus disponible."<<endl;
		}
 };
 
 class Exemplaire{
	private:
		Oeuvre const &oeuvre_;
	public:
		Exemplaire(Oeuvre const &oeuvre):oeuvre_(oeuvre){
			cout << "Nouvel exemplaire de : " << oeuvre_.getTitre()<< ", " <<
			oeuvre_.getAuteur().getNom()<<", en " << oeuvre_.getLangue() << endl;
		}
		Exemplaire(Exemplaire const &copie):oeuvre_(copie.oeuvre_){
			cout<<"Copie d'un exemplaire de : " << oeuvre_.getTitre() <<", "<<
			oeuvre_.getAuteur().getNom()<<", en " << oeuvre_.getLangue() << endl;
		}
		~Exemplaire(){
			cout<<"Un exemplaire de"<< " \" " << oeuvre_.getTitre()<<", "<<
			oeuvre_.getAuteur().getNom()<<", en " << oeuvre_.getLangue()<< " \" a été jeté !"<<endl;
		}
		Oeuvre const&getOeuvre() const{
			return oeuvre_;
		}
		void affiche(){
			cout<<"Exemplaire de : ";
			oeuvre_.affiche();
		}
 };
 
 class Bibliotheque{
	 private:
		string nom_;
		vector<Exemplaire*> exemplaires_;
	public:
		Bibliotheque(string nom):nom_(nom){
			cout<<"La bibliothèque "<<nom_<<" est ouverte !"<<endl;
		}
		string getNom(){
			return nom_;
		}
		void stocker(Oeuvre const &oeuvre, int nb_exemplaires=1){
			for (int i=0; i<nb_exemplaires; ++i){
				exemplaires_.push_back(new Exemplaire(oeuvre));
			}
		}
		void lister_exemplaires(string langue){
			for (vector<Exemplaire*>::iterator e=exemplaires_.begin() ; e!=exemplaires_.end(); ++e){
				if( (*e)->getOeuvre().getLangue()==langue )
					(*e)->affiche();
			}
		}
		void lister_exemplaires(){
			for (vector<Exemplaire*>::iterator e=exemplaires_.begin() ; e!=exemplaires_.end(); ++e){
					(*e)->affiche();
			}
		}
		
		int compter_exemplaires(Oeuvre const &oeuvre){
			int cpt=0;
			for (vector<Exemplaire*>::iterator e=exemplaires_.begin() ; e!=exemplaires_.end(); ++e){
				if( (*e)->getOeuvre().getAuteur().getNom()==oeuvre.getAuteur().getNom() &&
					(*e)->getOeuvre().getTitre()==oeuvre.getTitre() && (*e)->getOeuvre().getLangue()==oeuvre.getLangue() ){
					cpt+=1;
				}
			}
			return cpt;
		}
		
		void afficher_auteurs(bool prix=false){
			for (vector<Exemplaire*>::iterator e=exemplaires_.begin() ; e!=exemplaires_.end(); ++e){
				if( (prix ==true ) && ( (*e)->getOeuvre().getAuteur().getPrix() ==true) ){
						cout << (*e)->getOeuvre().getAuteur().getNom()<< endl;
					}
				else if (prix==false){
					cout << (*e)->getOeuvre().getAuteur().getNom() << endl;
				}
			}
		}
	
	~Bibliotheque(){
		cout << "La bibliothèque " <<nom_ << " ferme ses portes,"<<endl; cout<<" et détruit ses exemplaires :" << endl;
		for (vector<Exemplaire*>::iterator e=exemplaires_.begin() ; e!=exemplaires_.end(); ++e){
				delete *e;
		}
	}
 };
 
// Chaines de caractères à utiliser pour les affichages:
/*

été jeté

d'un

n'est

L'oeuvre

bibliothèque

détruit

*/

/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}

