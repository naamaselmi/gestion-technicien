#include "etudiant.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Etudiant::Etudiant(int id, QString nom ,QString prenom)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
}


bool Etudiant::ajouter()
{
    QSqlQuery q;
    q.prepare("insert into etudiant (id,nom,prenom)""values(:id, :nom, :prenom)");
    q.bindValue(":id",id);
    q.bindValue(":nom",nom);
    q.bindValue(":prenom",prenom);
    return q.exec();
}
 bool Etudiant::suprimer(int id)
 {
     QSqlQuery q ;
     QString res=QString::number(id);
     q.prepare("Delete from etudiant where ID= :id");
     q.bindValue(":id",res);
     return q.exec();

 }
 QSqlQueryModel * Etudiant::afficher()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from etudiant");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
     return model;
 }


 Etudiant Etudiant::findById(int id) {
     QSqlQuery query;
     query.prepare("SELECT * FROM etudiant WHERE ID = :id");
     query.bindValue(":id", id);

     if (query.exec()) {
         if (query.next()) { // If student is found
             Etudiant E;
             E.id = query.value("id").toInt();
             E.nom = query.value("nom").toString();
             E.prenom = query.value("prenom").toString();
             return E;
         }
     }

     // If not found, return an Etudiant object with id set to -1 to indicate not found
     Etudiant E;
     E.id = -1;
     return E;
 }


 bool Etudiant::mettreAJour(int newId) {
     QSqlQuery query;

     // Prepare the SQL statement to update the student data
     query.prepare("UPDATE etudiants SET id = :newId, nom = :nom, prenom = :prenom WHERE id = :currentId");
     query.bindValue(":newId", newId);
     query.bindValue(":nom", this->nom);
     query.bindValue(":prenom", this->prenom);
     query.bindValue(":currentId", this->id);

     // Execute the query and return true if successful, otherwise false
     if (query.exec()) {
         this->id = newId;  // Update the object's id attribute to the new ID
         return true;
     } else {
         return false;
     }
 }
