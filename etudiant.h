#ifndef ETUDIANT_H
#define ETUDIANT_H
#include<QSqlQuery>
#include<QSqlQueryModel>





class Etudiant
{
    QString nom, prenom;
    int id;
public:
    Etudiant(){};
    Etudiant (int ,QString,QString);

    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    int getID(){return id;}
    Etudiant findById(int id);
    bool mettreAJour(int newId);
    void setNom (QString n){nom=n;}
    void setPrenom (QString p){prenom=p;}
    void setID (int id ){this->id=id;}
    bool ajouter();
    QSqlQueryModel * afficher ();
    bool suprimer (int);
};

#endif // ETUDIANT_H
