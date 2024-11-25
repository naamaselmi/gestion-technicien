#include "technicien.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsqlerror.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>


technicien::technicien(int id, QString nom ,QString prenom,QString competence ,QString disponibilite,QString phoneNumber,QString absent ,QString adresse)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->competence=competence;
    this->disponibilite=disponibilite;
    this->phoneNumber=phoneNumber;
    this->absent=absent;
    this->adresse=adresse;

}
bool technicien::ajouter()
{
    QSqlQuery q;
    q.prepare("insert into technicien (id,nom,prenom,competence,disponibilite,phoneNumber,absent,adresse)""values(:id, :nom, :prenom, :competence, :disponibilite, :phoneNumber, :absent,:adresse)");
    q.bindValue(":id",id);
    q.bindValue(":nom",nom);
    q.bindValue(":prenom",prenom);
    q.bindValue(":competence",competence);
    q.bindValue(":disponibilite",disponibilite);
    q.bindValue(":phoneNumber",phoneNumber);
    q.bindValue(":absent",absent);
    q.bindValue(":adresse",adresse);
    return q.exec();


}
 bool technicien::supprimer(int id)
 {
     QSqlQuery q ;
     //QString res=QString::number(id);
     q.prepare("DELETE FROM technicien WHERE id= :id");
     q.bindValue(":id",id);
     return q.exec();

 }


 technicien technicien::findById(int id) {
     QSqlQuery query;
     query.prepare("SELECT * FROM technicien WHERE ID = :id");
     query.bindValue(":id", id);

     if (query.exec()) {
         if (query.next()) { // If technicien is found
             technicien t;
             t.id = query.value("id").toInt();
             t.nom = query.value("nom").toString();
             t.prenom = query.value("prenom").toString();
             t.competence = query.value("competence").toString();
             t.disponibilite = query.value("disponibilite").toString();
             t.phoneNumber = query.value("phoneNumber").toString();
             t.absent = query.value("absent").toString();
             t.adresse = query.value("adresse").toString();

             return t;}
     }
     // If not found, return an technicien object with id set to -1 to indicate not found
     technicien t;
     t.id = -1;
     return t;
 }
 technicien technicien::findByName(const QString& name) {
     QSqlQuery query;
     query.prepare("SELECT * FROM technicien WHERE nom = :name");
     query.bindValue(":name", name);

     if (query.exec()) {
         if (query.next()) { // If technicien is found
             technicien t;
             t.id = query.value("id").toInt();
             t.nom = query.value("nom").toString();
             t.prenom = query.value("prenom").toString();
             t.competence = query.value("competence").toString();
             t.disponibilite = query.value("disponibilite").toString();
             t.phoneNumber = query.value("phoneNumber").toString();
             t.absent = query.value("absent").toString();
             t.adresse = query.value("adresse").toString();

             return t;
         }
     }

     // If not found, return a technicien object with id set to -1 to indicate not found
     technicien t;
     t.id = -1;
     return t;
 }


 bool technicien::mettreAJour(int newId) {
     QSqlQuery q;
     // Prepare the SQL statement to update the student data
     q.prepare("UPDATE technicien SET id = :newId, nom = :nom, prenom = :prenom, competence = :competence, disponibilite = :disponibilite ,absent =:absent ,adresse= :adresse WHERE id = :currentId");
     q.bindValue(":newId", newId);
     q.bindValue(":nom", this->nom);
     q.bindValue(":prenom", this->prenom);
     q.bindValue(":competence", this->competence);
     q.bindValue(":disponibilite", this->disponibilite);
     q.bindValue(":currentId", this->id);
     q.bindValue(":phoneNumber", this->phoneNumber);
     q.bindValue(":absent", this->absent);
     q.bindValue(":adresse", this->adresse);

     // Execute the query and return true if successful, otherwise false
     if (q.exec()) {
         this->id = newId;  // Update the object's id attribute to the new ID
         return true;
     } else {
         return false;
     }
 }
 technicien technicien::findByCompetence(const QString& competence) {
     QSqlQuery query;
     query.prepare("SELECT * FROM technicien WHERE competence = :competence");
     query.bindValue(":competence", competence);

     if (query.exec()) {
         if (query.next()) { // If technicien is found
             technicien t;
             t.id = query.value("id").toInt();
             t.nom = query.value("nom").toString();
             t.prenom = query.value("prenom").toString();
             t.competence = query.value("competence").toString();
             t.disponibilite = query.value("disponibilite").toString();
             t.phoneNumber = query.value("phoneNumber").toString();
             t.absent = query.value("absent").toString();
             t.adresse = query.value("adresse").toString();

             return t;
         }
     }

     // If not found, return a technicien object with id set to -1 to indicate not found
     technicien t;
     t.id = -1;
     return t;
 }


 bool technicien::convertirEnPDF(const QString &filePath) const {
     // Create a QPdfWriter with the specified file path
     QPdfWriter pdfWriter(filePath);
     pdfWriter.setPageSize(QPageSize(QPageSize::A4));    // Set page size
     pdfWriter.setResolution(300);                       // Set resolution (DPI)
     pdfWriter.setTitle("Technicien Report");

     // Create a QPainter to draw on the PDF
     QPainter painter(&pdfWriter);

     if (!painter.isActive()) {
         return false; // Return false if the painter failed to activate
     }

     // Set fonts and basic styles
     QFont titleFont("Arial", 16, QFont::Bold);
     QFont contentFont("Arial", 12);

     painter.setFont(titleFont);
     painter.drawText(100, 100, QObject::tr("Technicien Report"));

     // Move down a bit and draw the content
     painter.setFont(contentFont);
     painter.drawText(100, 200, QObject::tr("Technicien ID: %1").arg(getID()));
     painter.drawText(100, 250, QObject::tr("Nom: %1").arg(getNom()));
     painter.drawText(100, 300, QObject::tr("Prénom: %1").arg(getPrenom()));
     painter.drawText(100, 350, QObject::tr("Compétence: %1").arg(getcompetence()));
     painter.drawText(100, 400, QObject::tr("Disponibilité: %1").arg(getdisponibilite()));
     painter.drawText(100, 450, QObject::tr("phoneNumber: %1").arg(getphoneNumber()));
     painter.drawText(100, 500, QObject::tr("absent: %1").arg(getabsent()));
     painter.drawText(100, 550, QObject::tr("adresse: %1").arg(getadresse()));

     // End the painter to finalize the PDF
     painter.end();

     return true;  // Return true if successful
 }




 bool technicien::convertirEnPDFAbsents(const QString &filePath, const QList<technicien> &techniciensAbsents) {
     // Create a QPdfWriter with the specified file path
     QPdfWriter pdfWriter(filePath);
     pdfWriter.setPageSize(QPageSize(QPageSize::A4));    // Set page size
     pdfWriter.setResolution(300);                       // Set resolution (DPI)
     pdfWriter.setTitle("Bilan des Absences");

     // Create a QPainter to draw on the PDF
     QPainter painter(&pdfWriter);

     if (!painter.isActive()) {
         return false; // Return false if the painter failed to activate
     }

     // Set fonts and basic styles
     QFont titleFont("Arial", 20, QFont::Bold);
     QFont headerFont("Arial", 14, QFont::Bold);
     QFont contentFont("Arial", 12);

     // Title - Centered in red
     painter.setFont(titleFont);
     painter.setPen(Qt::red);
     QRect titleRect(0, 50, pdfWriter.width(), 100);
     painter.drawText(titleRect, Qt::AlignCenter, QObject::tr("Bilan des Absences"));

     // Move down for the content
     painter.setPen(Qt::black);
     painter.setFont(headerFont);
     int yPosition = 250;  // Starting position for the table

     // Table headers with better spacing
     int columnX[] = {100, 300, 500, 800, 1300, 1700};  // X positions for each column
     painter.drawText(columnX[0], yPosition, QObject::tr("ID"));
     painter.drawText(columnX[1], yPosition, QObject::tr("Nom"));
     painter.drawText(columnX[2], yPosition, QObject::tr("Prénom"));
     painter.drawText(columnX[3], yPosition, QObject::tr("Compétence"));
     painter.drawText(columnX[4], yPosition, QObject::tr("Téléphone"));
     painter.drawText(columnX[5], yPosition, QObject::tr("Adresse"));

     // Draw a line under the headers
     yPosition += 20;
     painter.drawLine(100, yPosition, pdfWriter.width() - 100, yPosition);

     // Set content font
     painter.setFont(contentFont);
     yPosition += 250;  // Start content after header

     // Populate rows with absent technicians
     for (const technicien &t : techniciensAbsents) {
         if (t.getabsent().toLower() == "oui") { // Check if the technician is absent
             painter.drawText(columnX[0], yPosition, QString::number(t.getID()));
             painter.drawText(columnX[1], yPosition, t.getNom());
             painter.drawText(columnX[2], yPosition, t.getPrenom());
             painter.drawText(columnX[3], yPosition, t.getcompetence());
             painter.drawText(columnX[4], yPosition, t.getphoneNumber());
             painter.drawText(columnX[5], yPosition, t.getadresse());
             yPosition += 60;  // Increase the yPosition for the next row

             // Handle page break if reaching the end of the page
             if (yPosition > pdfWriter.height() - 100) {
                 pdfWriter.newPage();
                 yPosition = 100; // Reset y position for the new page
             }
         }
     }

     // End the painter to finalize the PDF
     painter.end();

     return true;  // Return true if successful
 }



 QSqlQueryModel* technicien::trier(const QString& critere, const QString& ordre) {
     QSqlQueryModel* model = new QSqlQueryModel();

     QString queryStr = "SELECT * FROM technicien ORDER BY " + critere + " " + ordre;
     model->setQuery(queryStr);

     if (model->lastError().isValid()) {
         qDebug() << "Erreur de tri:" << model->lastError().text();
         return nullptr;
     }

     return model;
 }



 QSqlQueryModel* technicien::getAbsentTechniciens() {
     QSqlQueryModel *model = new QSqlQueryModel();

         // Utilisation de 'oui' pour la colonne 'absent', et sélection de tous les techniciens absents
         model->setQuery("SELECT id, nom, prenom, phoneNumber FROM technicien WHERE absent = 'oui'");

         // Vérification des erreurs de requête
         if (model->lastError().isValid()) {
             qDebug() << "Error in query: " << model->lastError().text();
         }

         // Définition des en-têtes du modèle
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro de téléphone"));

         return model;
 }

 QSqlQueryModel* technicien::obtenirStatistiquesCompetence() {
     QSqlQueryModel* model = new QSqlQueryModel();

     // SQL Query to get competence and count of technicians for each competence
     QSqlQuery query;
     query.prepare("SELECT competence, COUNT(*) as nombre FROM technicien GROUP BY competence");

     // Execute the query and check for success
     if (!query.exec()) {
         qWarning() << "Query failed:" << query.lastError().text();  // Log if there's an error
         return model;  // Return empty model in case of error
     }

     model->setQuery(query);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Compétence"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre"));

     return model;
 }

