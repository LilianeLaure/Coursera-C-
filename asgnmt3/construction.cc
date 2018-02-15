#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
    Brique(Forme , Couleur );
    ostream& afficher(ostream& sortie) const;
};

Brique::Brique(Forme f, Couleur c): forme(f), couleur(c){}

ostream& Brique:: afficher(ostream& sortie) const
{
    if(!couleur.empty())
    {
        sortie << "(" << forme << ", " << couleur << ")";
    }
    else
    {
        sortie << forme;
    }
    return sortie;
}

ostream &operator << (ostream & sortie, Brique const &b)
{
   return b.afficher(sortie);
}

class Construction
{
  friend class Grader;

   public :
	Construction(Brique const& brique);
	friend ostream &operator << (ostream & sortie, Construction const &c);
	Construction& operator ^=(Construction const &c);
	Construction& operator -=(Construction const &c);
	Construction& operator +=(Construction const &c);
	ostream& afficher(ostream& sortie) const;

  private:
	vector< vector <vector <Brique> > >  contenu;

};
Construction :: Construction(Brique const& brique):contenu(1,vector<vector<Brique> >(1,vector <Brique>(1,brique)))
{}

ostream& Construction:: afficher(ostream& sortie) const
{
	for(size_t i=contenu.size()-1; i>=0 && i < contenu.size() ; i--)
	{
	   cout<<"Couche "<<i<<" : "<<endl;
		for(auto &j : contenu[i])
		{
			for(auto &k : j)
			{
				sortie<<k<<" ";
			}
			cout<<endl;
		}
	}
	return sortie;
}

ostream& operator << (ostream& sortie, Construction const &c)
{
   return c.afficher(sortie);
}

Construction& Construction :: operator ^=(Construction const &c)
{
	contenu.insert(contenu.end(), c.contenu.begin(), c.contenu.end() );
	return *this;
}

const Construction operator^(Construction a,Construction const& b) {
	a^=b;
	return a;
}

Construction& Construction :: operator -=(Construction const &c)
{
	if(c.contenu.size() >= contenu.size())
	{
		for(size_t i=0 ; i< contenu.size() ; ++i )
		{
			contenu[i].insert(contenu[i].end(), c.contenu[i].begin(), c.contenu[i].end());
		}
	}
	return *this;
}

const Construction operator-(Construction a,Construction const& b) {
	a-=b;
	return a;
}

Construction& Construction :: operator +=(Construction const &c)
{
	if(c.contenu.size() >= contenu.size())
	{
		if(c.contenu[0].size() >= contenu[0].size())
		{
			for(size_t i=0 ; i< contenu.size() ; ++i )
			{
				for(size_t j=0; j< contenu[0].size() ; j++ )
				{
					contenu[i][j].insert(contenu[i][j].end(), c.contenu[i][j].begin(), c.contenu[i][j].end());
				}
			}
		}
	}
	return *this;
}

const Construction operator+(Construction a,Construction const& b)
{
	a+=b;
	return a;
}

const Construction operator*(unsigned int n, Construction const& a)
{
    Construction c=a;
	for ( unsigned int i=0; i<n-1; ++i )
	{
		c+=a;
	}
	return c;
}

const Construction operator/(unsigned int n, Construction const& a)
{
    Construction c=a;
	for ( unsigned int i=0; i<n-1; ++i )
	{
		c^=a;
	}
	return c;
}

const Construction operator%(unsigned int n, Construction const& a)
{
    Construction c=a;
	for ( unsigned int i=0; i<n-1; ++i )
	{
		c-=a;
	}
	return c;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}

