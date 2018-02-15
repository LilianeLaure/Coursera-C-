#include <iostream>
#include <cmath>
using namespace std;

enum Pavillon { JollyRogers, CompagnieDuSenegal, CompagnieDOstende };

enum Etat { Intact, Endommage, Coule };

int sq(int x)
{
  return x*x;
}

class Coordonnees
{
public:
  Coordonnees(int un_x, int un_y) : x_(un_x), y_(un_y) {}
  int x() const {
    return x_;
  }
  int y() const {
    return y_;
  }
  void operator+=(Coordonnees const& autre); // à définir plus bas
private:
  int x_;
  int y_;
};

class Navire
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

   protected :
   	Coordonnees position_;
   	Pavillon pavillon_;
   	Etat etat_;

   public :
   	const int rayon_rencontre=10;
   	Navire(int x, int y, Pavillon pavillon):
   		position_(x,y), pavillon_(pavillon),etat_(Intact)
   		{}
   	Coordonnees position() const{
   		return position_;
    }
    Etat get_etat() const{
		return etat_;
	}
   	void avancer(int de_x, int de_y){
   		if(etat_!=Coule)
   		{
   			const Coordonnees point(de_x, de_y);
   			position_+=point;
   		}
   	}
   	void renflouer()
   	{
   		etat_=Intact;
   	}
   	virtual void attaque( Navire &autre ) =0;
 	virtual void replique( Navire &autre ) =0;
 	virtual void est_touche()=0;
 	virtual void rencontrer(Navire &autre);
	virtual ostream& afficher(ostream& os) const;
	friend ostream& operator<<(ostream& os, Navire const& navire);
};
double distance(const Coordonnees& un, const Coordonnees& deux)
{
	return sqrt( sq(un.x()-deux.x() )+ sq( un.y()-deux.y() ) );
}

double distance(const Navire & n1, const Navire & n2)
{
	return distance(n1.position() , n2.position());
}

ostream& operator<<(ostream& os, Coordonnees const& point)
{
	os << "(" << point.x() <<", " << point.y() << ")";
	return os;
}

void Navire::rencontrer(Navire &autre){
	if( (etat_!=Coule) && (autre.etat_!=Coule) && (pavillon_!=autre.pavillon_) && (distance(*this, autre) <= Navire::rayon_rencontre) )
	{
		attaque(autre);
		autre.replique(*this); //a voir
	}
}

ostream& operator<<(ostream& os, Pavillon const& pavillon)
{
	if(pavillon==JollyRogers)
		os << "pirate";
	else if(pavillon==CompagnieDuSenegal)
		os << "français";
	else if(pavillon==CompagnieDOstende)
		os << "autrichien";
	else
		os << "pavillon inconnu";
	return os;
}

ostream& operator<<(ostream& os, Etat const& etat)
{
	if(etat==Intact)
		os << "intact";
	else if(etat==Endommage)
		os << "ayant subi des dommages";
	else if(etat==Coule)
		os << "coulé";
	else
		os << "état inconnu";
	return os;
}

ostream& Navire::afficher(ostream& os) const
{
	os << "en " << position_ << " battant pavillon " << pavillon_ << ", " << etat_;
	return os;
}

ostream& operator<<(ostream& os, Navire const& navire)
{
	return navire.afficher(os);
}

class Marchand : public virtual Navire{
	public :
		Marchand(int x, int y, Pavillon pavillon):Navire(x, y, pavillon){}

		void attaque(Navire & autre)
		{
			if(autre.get_etat()!=Coule && get_etat()!=Coule){
				cout << " On vous aura ! (insultes) " << endl;
			}
		}
		void replique(Navire & autre)
		{
			if(etat_==Coule)
				cout <<"SOS je coule ! " << endl;
			else
				cout << "Même pas peur ! "<< endl;
		}
		void est_touche()
		{
			etat_=Coule;
		}
		ostream& afficher(ostream& os) const
		{
			os <<"navire marchand ";
			Navire::afficher(os);
			return os;
		}

};

class Pirate : public virtual Navire{

	public :
		Pirate(int x, int y, Pavillon pavillon):
			Navire(x, y, pavillon){}

		void attaque(Navire & autre)
		{
			if(autre.get_etat()!=Coule && get_etat()!=Coule){
				cout << "A l'abordage ! " << endl;
				autre.est_touche();
			}
		}
		void replique(Navire & autre)
		{
			if(etat_!=Coule)
			{
				cout << "Non mais, ils nous attaquent ! On riposte !! " << endl;
				attaque(autre);
			}
		}
		void est_touche()
		{
			if(etat_==Intact)
				etat_=Endommage;
			else if(etat_==Endommage)
				etat_=Coule;
		}
		ostream& afficher(ostream& os) const
		{
			os <<"bateau pirate ";
			Navire::afficher(os);
			return os;
		}
};



class Felon : public Marchand, public Pirate{
	public :
		Felon(int x, int y, Pavillon pavillon):
			Navire(x, y, pavillon), Marchand(x,y,pavillon), Pirate(x,y,pavillon)
			{}
		void attaque(Navire& n)
		{
			Pirate::attaque(n);
		}
	void replique(Navire& n)
	{
		Marchand::replique(n);
	}
	void est_touche()
	{
		Pirate::est_touche();
	}
	ostream& afficher(ostream &os) const
	{
		os <<"navire félon ";
		Navire::afficher(os);
		return os;
	}
};

void Coordonnees::operator+=(Coordonnees const& autre)
{
  // à définir ici
  x_+=autre.x_;
  y_+=autre.y_;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void rencontre(Navire& ship1, Navire& ship2)
{
  cout << "Avant la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
  cout << "Distance : " << distance(ship1, ship2) << endl;
  ship1.rencontrer(ship2);
  cout << "Apres la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
}

int main()
{
  // Test de la partie 1
  cout << "===== Test de la partie 1 =====" << endl << endl;

  // Un bateau pirate 0,0
  Pirate ship1(0, 0, JollyRogers);
  cout << ship1 << endl;

  // Un bateau marchand en 25,0
  Marchand ship2(25, 0, CompagnieDuSenegal);
  cout << ship2 << endl;

  cout << "Distance : " << distance(ship1, ship2) << endl;

  cout << "Quelques déplacements..." << endl;
  cout << "  en haut à droite :" << endl;
  // Se déplace de 75 unités à droite et 10 en haut
  ship1.avancer(75, 10);
  cout << ship1 << endl;

  cout << "  vers le bas :" << endl;
  ship1.avancer(0, -5);
  cout << ship1 << endl;

  cout << endl << "===== Test de la partie 2 =====" << endl << endl;

  cout << "Bateau pirate et marchand ennemis (trop loins) :" << endl;
  rencontre(ship1, ship2);

  cout << endl << "Bateau pirate et marchand ennemis (proches) :" << endl;
  ship1.avancer(-40, -2);
  ship2.avancer(10, 2);
  rencontre(ship1, ship2);

  cout << endl << "Deux bateaux pirates ennemis intacts (proches) :" << endl;
  Pirate ship3(33, 8, CompagnieDOstende);
  rencontre(ship1, ship3);

  cout << endl << "Bateaux pirates avec dommages, ennemis :" << endl;
  rencontre(ship1, ship3);

  cout << endl << "Bateaux marchands ennemis :" << endl;
  Marchand ship4(21, 7, CompagnieDuSenegal);
  Marchand ship5(27, 2, CompagnieDOstende);
  rencontre(ship4, ship5);

  cout << endl << "Pirate vs Felon :" << endl;
  ship3.renflouer();
  Felon ship6(32, 10, CompagnieDuSenegal);
  rencontre(ship3, ship6);

  cout << endl << "Felon vs Pirate :" << endl;
  rencontre(ship6, ship3);

  return 0;
}

