#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
    Flacon(string n, double v, double ph);
    ostream& etiquette(ostream& sortie) const;
    friend ostream &operator << (ostream & sortie, Flacon const &f);
    Flacon operator +(Flacon const &f ) const;
    Flacon& operator +=(Flacon const &f );
};
    Flacon::Flacon(string n, double v, double ph):nom(n),volume(v),pH(ph){}

    ostream& Flacon::etiquette(ostream& sortie) const
    {
        sortie << nom << " : " << volume << " mL, " << "pH " << pH;
        return sortie;
    }

    ostream &operator << (ostream & sortie, Flacon const &f)
    {
       return f.etiquette(sortie);
    }

    Flacon Flacon::operator +(Flacon const &f ) const
    {
       double pH_f=-log10( (volume*pow(10, -pH) + f.volume*pow(10, -f.pH))/(volume+f.volume) );
       return Flacon(nom+" + "+f.nom, volume+f.volume, pH_f);

    }

    Flacon& Flacon::operator +=(Flacon const &f )
    {
        nom+=" " + f.nom;
        volume+= f.volume;
       pH=-log10( (volume*pow(10, -pH) + f.volume*pow(10, -f.pH))/(volume+f.volume) );
       return *this;

	}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);

  return 0;

}

