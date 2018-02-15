#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/

class Produit{
protected:
	string nom_;
	string unite_;
public:
	Produit(string nom, string unite=""): nom_(nom), unite_(unite)
	{}
	string getNom() const{
		return nom_;
	}
	string getUnite() const{
		return unite_;
	}
	virtual string toString() const{
		return nom_;
	}
	virtual const Produit* adapter(double n) const{
		return this;
	}
	virtual double quantiteTotale(const string& nomProduit) const{
		if(getNom()==nomProduit){
			return 1;
		}
		return 0;
	}
	virtual ~Produit(){};
};

class Ingredient{
public:
	Ingredient(const Produit& produit, double quantite):produit_(produit),quantite_(quantite)
	{}
	const Produit & getProduit() const{
		return produit_;
	}
	double getQuantite() const {
		return quantite_;
	}
	string descriptionAdaptee() const{
		stringstream ss;
        const Produit* temp = produit_.adapter(quantite_);
        ss << fixed << getQuantite() << " " << produit_.getUnite() << " de " << temp->toString();
        return ss.str();
	}
	double quantiteTotale(const string& nomProduit) const{
		return getQuantite()*getProduit().quantiteTotale(nomProduit);
	}
private:
	const Produit& produit_;
	double quantite_;
};

class Recette{
public:
	Recette(string nom, double nbFois=1.0):_nom(nom), nbFois_(nbFois)
	{}
	void ajouter(const Produit& p, double quantite){
		ingredients.push_back(Ingredient(p, quantite*nbFois_));
	}
	Recette adapter(double n) const
	{
		Recette recette_n(_nom, n*nbFois_);
		for(auto const & it : ingredients)
		{
			recette_n.ingredients.push_back(Ingredient(it.getProduit(), it.getQuantite()*n));;
		}
		return recette_n;
	}
	string toString() const{
        stringstream ss;
		ss << " Recette \"" << _nom << "\" x " << nbFois_<< ":\n";
		unsigned int i = 1;
		for (auto const & ingredient : ingredients){
			ss << " " << i << ". " << ingredient.descriptionAdaptee();
			if (i != ingredients.size()){
				ss << endl;
			}
			i += 1;
		}
		string s = ss.str();
		return s;
    }

	double quantiteTotale(const string& nomProduit) const{
		double somme=0.0;
		for(auto const & it : ingredients){
			somme+=it.quantiteTotale(nomProduit);
		}
		return somme;
	}

private:
	vector<Ingredient> ingredients;
	string _nom;
	double nbFois_;
};

class ProduitCuisine : public Produit{
public:
	ProduitCuisine(string nom):Produit(nom, "portion(s)"),recette_(Recette(nom))
	{}
	~ProduitCuisine(){}
	void ajouterARecette(const Produit& produit, double quantite){
		recette_.ajouter(produit, quantite);
	}
	const Produit * adapter(double n) const override{
		ProduitCuisine *neuf=new ProduitCuisine(nom_);
		neuf->recette_=recette_.adapter(n);
		return neuf;
	}
	string toString() const override{
		stringstream ss;
		ss << Produit::toString() << "\n" << recette_.toString();
		return ss.str();
	}
	double quantiteTotale(const string& nomProduit) const override{
		if(getNom()==nomProduit)
			return 1.0;
		return recette_.quantiteTotale(nomProduit);
	}
private:
	Recette recette_;
};



/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
  string nom = produit.getNom();
  cout << "Cette recette contient " << recette.quantiteTotale(nom)
       << " " << produit.getUnite() << " de " << nom << endl;
}

int main()
{
  // quelques produits de base
  Produit oeufs("oeufs");
  Produit farine("farine", "grammes");
  Produit beurre("beurre", "grammes");
  Produit sucreGlace("sucre glace", "grammes");
  Produit chocolatNoir("chocolat noir", "grammes");
  Produit amandesMoulues("amandes moulues", "grammes");
  Produit extraitAmandes("extrait d'amandes", "gouttes");

  ProduitCuisine glacage("glaçage au chocolat");
  // recette pour une portion de glaçage:
  glacage.ajouterARecette(chocolatNoir, 200);
  glacage.ajouterARecette(beurre, 25);
  glacage.ajouterARecette(sucreGlace, 100);
  cout << glacage.toString() << endl;

  ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
  // besoin de 1 portions de glaçage au chocolat et de 2 gouttes
  // d'extrait d'amandes pour 1 portion de glaçage parfumé

  glacageParfume.ajouterARecette(extraitAmandes, 2);
  glacageParfume.ajouterARecette(glacage, 1);
  cout << glacageParfume.toString() << endl;

  Recette recette("tourte glacée au chocolat");
  recette.ajouter(oeufs, 5);
  recette.ajouter(farine, 150);
  recette.ajouter(beurre, 100);
  recette.ajouter(amandesMoulues, 50);
  recette.ajouter(glacageParfume, 2);

  cout << "===  Recette finale  =====" << endl;
  cout << recette.toString() << endl;
  afficherQuantiteTotale(recette, beurre);
  cout << endl;

  // double recette
  Recette doubleRecette = recette.adapter(2);
  cout << "===  Recette finale x 2 ===" << endl;
  cout << doubleRecette.toString() << endl;

  afficherQuantiteTotale(doubleRecette, beurre);
  afficherQuantiteTotale(doubleRecette, oeufs);
  afficherQuantiteTotale(doubleRecette, extraitAmandes);
  afficherQuantiteTotale(doubleRecette, glacage);
  cout << endl;

  cout << "===========================\n" << endl;
  cout << "Vérification que le glaçage n'a pas été modifié :\n";
  cout << glacage.toString() << endl;

  return 0;
}

