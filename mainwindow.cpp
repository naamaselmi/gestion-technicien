#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "technicien.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QRegularExpression>
#include <QVector>
#include <QPair>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QSslSocket>
#include <QSqlError>
#include <QDesktopServices>
#include <QRegularExpression>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon("C:/NAARACH/Atelier_Connexion (1)/Atelier_Connexion/AUTACARE.png"));
    ui->setupUi(this);
    ui->tableView->setModel(tech.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    bool ok;
    int id = ui->idtech->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("L'ID doit être un nombre entier."),
                             QMessageBox::Ok);
        return;
    }

    // Expression régulière pour les lettres uniquement
    QRegularExpression lettersRegex("^[A-Za-zÀ-ÿ]+$");

    QString nom = ui->nomtech->text();
    if (nom.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ Nom ne peut pas être vide."),
                             QMessageBox::Ok);
        return;
    } else if(!lettersRegex.match(nom).hasMatch()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ Nom doit contenir uniquement des lettres."),
                             QMessageBox::Ok);
        return;
    }

    QString prenom = ui->pretech->text();
    if (prenom.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ Prénom ne peut pas être vide."),
                             QMessageBox::Ok);
        return;
    } else if(!lettersRegex.match(prenom).hasMatch()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ Prénom doit contenir uniquement des lettres."),
                             QMessageBox::Ok);
        return;
    }

    QString competence = ui->competence->text();
    if (competence.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ Compétence ne peut pas être vide."),
                             QMessageBox::Ok);
        return;
    } else if(!lettersRegex.match(competence).hasMatch()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ Compétence doit contenir uniquement des lettres."),
                             QMessageBox::Ok);
        return;
    }

    QString disponibilite = ui->dispotech->text();
    if (disponibilite.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ Disponibilité ne peut pas être vide."),
                             QMessageBox::Ok);
        return;
    } else if(!lettersRegex.match(disponibilite).hasMatch()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ Disponibilité doit contenir uniquement des lettres."),
                             QMessageBox::Ok);
        return;
    }

    QString phoneNumber = ui->tel->text();
    if (phoneNumber.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ N°téléphone ne peut pas être vide."),
                             QMessageBox::Ok);
        return;
    }

    QRegularExpression phoneRegex("^[0-9]{8}$");
    QRegularExpressionMatch phoneMatch = phoneRegex.match(phoneNumber);

    if (!phoneMatch.hasMatch()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ N°téléphone doit contenir exactement 8 chiffres."),
                             QMessageBox::Ok);
        return;
    }

    QString absent = ui->absence->text();
    if (absent.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ Absent ne peut pas être vide."),
                             QMessageBox::Ok);
        return;
    }

    if (absent.compare("oui", Qt::CaseInsensitive) != 0 &&
        absent.compare("non", Qt::CaseInsensitive) != 0) {
        QMessageBox::warning(this, tr("Erreur de saisie"),
                             tr("Le champ Absent doit contenir 'oui' ou 'non'."),
                             QMessageBox::Ok);
        return;
    }

    QString adresse = ui->adresse->text().trimmed();

        // Vérification de base
        if (adresse.isEmpty()) {
            QMessageBox::warning(this, tr("Erreur de saisie"),
                                tr("Le champ Adresse ne peut pas être vide."),
                                QMessageBox::Ok);

            return;
        }



    technicien t(id, nom, prenom, competence, disponibilite, phoneNumber, absent, adresse);
    bool test = t.ajouter();

    if (test) {
        QMessageBox::information(this, tr("OK"),
                                 tr("Ajout effectué\nCliquez sur Cancel pour quitter."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(this, tr("NOT OK"),
                                 tr("Ajout non effectué\nCliquez sur Cancel pour quitter."), QMessageBox::Cancel);
    }
}


void MainWindow::on_supprimer_clicked()
{
    int id = ui->idtechsupp->text().toInt();
    bool test = tech.supprimer(id);

    if (test) {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                QObject::tr("Suppression effectué\nCliquez sur Cancel pour quitter."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(this, tr("NOT OK"),
                                 tr("Suppression non effectué\nCliquez sur Cancel pour quitter."), QMessageBox::Cancel);
    }
}



void MainWindow::on_miseajour_clicked()
{
    int id = ui->idtech2->text().toInt(); // Updated to match XML
       QString nom = ui->nomtech2->text();
       QString prenom = ui->pretech2->text();
       QString competence = ui->competence2->text();
       QString disponabilite = ui->dispotech2->text();
       QString phoneNumber = ui->tel2->text();
       QString absent = ui->absence2->text();
       QString adresse = ui->adresse2->text();




       technicien t(id, nom, prenom, competence, disponabilite, phoneNumber, absent  ,adresse);
       bool test = t.mettreAJour(id); // Assuming mettreAJour is defined correctly

       if (test) {
           QMessageBox::information(this, tr("Sauvegarde réussie"),
                                    tr("Les informations du technicien ont été mises à jour."));
       } else {
           QMessageBox::critical(this, tr("Erreur"),
                                 tr("La mise à jour des informations du technicien a échoué."),
                                 QMessageBox::Cancel);
       }

}


void MainWindow::on_exportExcel_clicked()
{
    // Ouvrir une boîte de dialogue pour sélectionner où sauvegarder le fichier
    QString fileName = QFileDialog::getSaveFileName(this,
        "Enregistrer le fichier Excel",
        "",
        "Fichier Excel (*.csv)");

    if (fileName.isEmpty()) {
        return;
    }

    // Ajouter automatiquement l'extension .csv si nécessaire
    if (!fileName.endsWith(".csv", Qt::CaseInsensitive)) {
        fileName += ".csv";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }

    // Créer un flux de texte avec l'encodage UTF-8 avec BOM pour Excel
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out.setGenerateByteOrderMark(true);

    // Fonction helper pour échapper les caractères spéciaux
    auto escapeCSV = [](const QString& str) -> QString {
        QString result = str;
        // Remplacer les points-virgules par des virgules
        result.replace(";", ",");
        // Si la chaîne contient des virgules, des guillemets ou des sauts de ligne
        if (result.contains(QRegExp("[,\"\n\r]"))) {
            // Échapper les guillemets en les doublant
            result.replace("\"", "\"\"");
            // Entourer la chaîne de guillemets
            result = "\"" + result + "\"";
        }
        return result;
    };

    // Écrire l'en-tête avec des points-virgules comme séparateurs
    out << "ID;Nom;Prénom;Compétence;Disponibilité;Téléphone;Absent;Adresse\n";

    // Récupérer les données
    QSqlQuery query;
    query.prepare("SELECT id, nom, prenom, competence, disponibilite, phoneNumber, absent ,adresse "
                 "FROM technicien");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur",
            "Erreur lors de la récupération des données des techniciens");
        return;
    }

    // Écrire les données
    while (query.next()) {
        QStringList row;
        // Récupérer et formater chaque champ
        for (int i = 0; i < 7; ++i) {
            row << escapeCSV(query.value(i).toString());
        }
        // Joindre les champs avec des points-virgules
        out << row.join(";") << "\n";
    }

    file.close();

    // Proposer d'ouvrir le fichier
    QMessageBox::StandardButton reply = QMessageBox::question(this,
        "Export terminé",
        "Les données ont été exportées avec succès. Voulez-vous ouvrir le fichier ?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    }
}




void MainWindow::on_recherche_clicked()
{
    // Get the ID entered by the user
    int id = ui->idtech2->text().toInt();

    // Search for the student using findById function
    technicien t = t.findById(id);

    // Check if the student was found
    if (t.getID() != -1) {
        // Display student details in the line edits
        ui->idtech2->setText(QString::number(t.getID()));
        ui->nomtech2->setText(t.getNom());
        ui->pretech2->setText(t.getPrenom());
        ui->competence2->setText(t.getcompetence());
        ui->dispotech2->setText(t.getdisponibilite());
        ui->tel2->setText(t.getphoneNumber());
        ui->absence2->setText(t.getabsent());
        ui->adresse2->setText(t.getadresse());


        // Show a message indicating that the technicien was found
        QMessageBox::information(this, tr("technicien trouvé"),
                                 tr("technicien trouvé."));
    } else {
        // Show an error message if the technicien is not found
        QMessageBox::critical(this, tr("Erreur"),
                              tr("technicien introuvable.\nVeuillez vérifier l'ID."),
                              QMessageBox::Cancel);

}}

QSqlQueryModel* technicien::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        // Utilisation d'une requête SQL explicite pour récupérer les colonnes dans l'ordre correct
        model->setQuery("SELECT id, nom, prenom, competence, disponibilite, phoneNumber, absent ,adresse FROM technicien");

        // Définition des en-têtes des colonnes
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Compétence"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Disponibilité"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Numéro de téléphone"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Absent"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Adresse"));

        return model;
}



void MainWindow::on_afficher_clicked()
{
    ui->tableView->setModel(tech.afficher());
}




void MainWindow::on_trier_clicked() {

    ui->tableView->setModel(tech.trier("id", "ASC"));
}

void MainWindow::on_trier_nom_clicked()
{
    ui->tableView->setModel(tech.trier("nom", "ASC"));
}
void MainWindow::on_trier_absence_clicked()
{
    ui->tableView->setModel(tech.trier("absent", "ASC"));
}

void MainWindow::on_statistique_clicked() {
    // 1. Obtenez les données de statistiques pour la compétence
    QSqlQueryModel* model = tech.obtenirStatistiquesCompetence();

    // Vérifiez que la requête a réussi
    if (model) {
        // Définir le modèle pour tableView_2 (le graphique en secteurs)
        ui->tableView_2->setModel(model);
        ui->tableView_2->resizeColumnsToContents();
        ui->tableView_2->resizeRowsToContents();

        // Créez l'image du graphique en secteurs
        QVector<QPair<QString, int>> chartData;
        for (int row = 0; row < model->rowCount(); ++row) {
            QString competence = model->data(model->index(row, 0)).toString();
            int count = model->data(model->index(row, 1)).toInt();
            chartData.append(qMakePair(competence, count));
        }

        // Créez l'image pour le graphique en secteurs (pie chart)
        const int pieChartWidth = 400;
        const int pieChartHeight = 400;
        QImage pieChartImage(pieChartWidth, pieChartHeight, QImage::Format_ARGB32);
        pieChartImage.fill(Qt::white);  // Remplir l'image avec un fond blanc

        QPainter pieChartPainter(&pieChartImage);
        pieChartPainter.setRenderHint(QPainter::Antialiasing);

        int total = 0;
        for (const auto &item : chartData) {
            total += item.second;
        }

        // Palette de couleurs modernes
        QVector<QColor> colorPalette = {
            QColor(255, 99, 71), // Tomato red
            QColor(70, 130, 180), // Steel blue
            QColor(34, 139, 34),  // Forest green
            QColor(255, 223, 0),  // Bright yellow
            QColor(255, 165, 0),  // Orange
            QColor(138, 43, 226), // Blue violet
            QColor(0, 255, 255)   // Cyan
        };

        int startAngle = 0;
        QRectF pieRect(50, 50, 300, 300);  // Définir la zone du graphique
        int colorIndex = 0;

        for (const auto &item : chartData) {
            int spanAngle = (item.second * 360) / total;  // Calculer l'angle de chaque secteur

            QColor color = colorPalette[colorIndex % colorPalette.size()];
            pieChartPainter.setBrush(color);
            pieChartPainter.drawPie(pieRect, startAngle * 16, spanAngle * 16);  // Dessiner chaque secteur

            // Ajouter le nom de la compétence sur la partie correspondante
            // Calculer la position pour le texte
            int midAngle = startAngle + spanAngle / 2;
            QPointF textPosition = pieRect.center();
            textPosition.setX(textPosition.x() + 150 * qCos(midAngle * M_PI / 180));
            textPosition.setY(textPosition.y() + 150 * qSin(midAngle * M_PI / 180));

            pieChartPainter.setPen(Qt::black);
            pieChartPainter.drawText(textPosition, item.first);  // Dessiner le nom de la compétence

            startAngle += spanAngle;
            colorIndex++;
        }

        // Convertir l'image en QPixmap pour l'afficher dans tableView_2
        QPixmap pieChartPixmap = QPixmap::fromImage(pieChartImage);

        // Créez un modèle QStandardItemModel pour tableView_2
        QStandardItemModel* pieChartModel = new QStandardItemModel(1, 1, this);  // 1 ligne, 1 colonne
        QStandardItem* pieChartItem = new QStandardItem();
        pieChartItem->setData(pieChartPixmap, Qt::DecorationRole);  // Affecter l'image au modèle

        pieChartModel->setItem(0, 0, pieChartItem);  // Ajouter l'élément au modèle
        ui->tableView_2->setModel(pieChartModel);  // Affecter le modèle à tableView_2

        // Ajuster la taille des colonnes et des lignes pour afficher correctement l'image
        ui->tableView_2->resizeColumnsToContents();
        ui->tableView_2->resizeRowsToContents();

        // 2. Créez l'image du graphique à barres pour tableView_3
        const int barChartWidth = 400;
        const int barChartHeight = 300;
        QImage barChartImage(barChartWidth, barChartHeight, QImage::Format_ARGB32);
        barChartImage.fill(Qt::white);  // Remplir l'image avec un fond blanc

        QPainter barChartPainter(&barChartImage);
        barChartPainter.setRenderHint(QPainter::Antialiasing);

        const int barWidth = 50;
        const int gap = 20;
        const int maxBarHeight = barChartHeight - 40;

        int barTotal = 0;
        for (const auto &item : chartData) {
            barTotal += item.second;
        }

        // Calculer le facteur d'échelle pour les barres
        float barScale = static_cast<float>(maxBarHeight) / barTotal;

        // Dessiner les barres
        int barXPos = 30;
        colorIndex = 0;
        for (const auto &item : chartData) {
            int barHeight = static_cast<int>(item.second * barScale);
            QRect barRect(barXPos, barChartHeight - barHeight - 20, barWidth, barHeight);

            QColor barColor = colorPalette[colorIndex % colorPalette.size()];
            barChartPainter.setBrush(barColor);
            barChartPainter.drawRect(barRect);  // Dessiner chaque barre

            barChartPainter.setPen(Qt::black);
            barChartPainter.drawText(barRect.center(), item.first);  // Ajouter le texte sous chaque barre

            barXPos += barWidth + gap;
            colorIndex++;
        }

        // Convertir l'image du graphique à barres en QPixmap pour tableView_3
        QPixmap barChartPixmap = QPixmap::fromImage(barChartImage);

        // Créez un modèle QStandardItemModel pour tableView_3
        QStandardItemModel* barChartModel = new QStandardItemModel(1, 1, this);  // 1 ligne, 1 colonne
        QStandardItem* barChartItem = new QStandardItem();
        barChartItem->setData(barChartPixmap, Qt::DecorationRole);  // Affecter l'image au modèle

        barChartModel->setItem(0, 0, barChartItem);  // Ajouter l'élément au modèle
        ui->tableView_3->setModel(barChartModel);  // Affecter le modèle à tableView_3

        // Ajuster la taille des colonnes et des lignes pour afficher correctement l'image
        ui->tableView_3->resizeColumnsToContents();
        ui->tableView_3->resizeRowsToContents();
    } else {
        QMessageBox::warning(this, tr("Erreur"), tr("Échec de la récupération des statistiques pour les graphiques."));
    }
}







void MainWindow::on_conversionenpdf_clicked()
{
    int id = ui->idtech->text().toInt();  // Récupère l'ID du technicien à partir de l'interface
    technicien t = tech.findById(id);      // Trouve le technicien correspondant à l'ID

    if (t.getID() == -1) {
        QMessageBox::warning(this, tr("Erreur"), tr("Technicien introuvable. Veuillez vérifier l'ID."));
        return;
    }

    QString nomFichier = QFileDialog::getSaveFileName(this, tr("Enregistrer en PDF"), "", "*.pdf");

    if (!nomFichier.isEmpty()) {
        if (t.convertirEnPDF(nomFichier)) {
            QMessageBox::information(this, tr("Succès"), tr("PDF créé avec succès."));
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("La création du PDF a échoué."));
        }
    }

}


PieChartWidget::PieChartWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(400, 400);  // Set a fixed size for the widget (adjust as needed)
}

void PieChartWidget::setData(const QVector<QPair<QString, int>> &data)
{
    chartData = data;
    update();  // Trigger repaint when data changes
}

void PieChartWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Total sum of the data for percentage calculations
    int total = 0;
    for (const auto &item : chartData) {
        total += item.second;
    }

    // Draw the pie chart
    int startAngle = 0;
    QRectF rect(50, 50, 300, 300);  // Rect for the pie chart
    for (const auto &item : chartData) {
        int spanAngle = (item.second * 360) / total;  // Convert value to angle for each slice

        QColor color;
        if (item.first == "Category 1") color = Qt::red;
        else if (item.first == "Category 2") color = Qt::blue;
        else color = Qt::green;

        painter.setBrush(color);
        painter.drawPie(rect, startAngle * 16, spanAngle * 16);

        startAngle += spanAngle;
    }

    // Optionally, you can draw labels here
    startAngle = 0;
    for (const auto &item : chartData) {
        int spanAngle = (item.second * 360) / total;
        QPointF labelPoint = rect.center();
        labelPoint.setX(labelPoint.x() + 150 * qCos((startAngle + spanAngle / 2) * M_PI / 180));
        labelPoint.setY(labelPoint.y() + 150 * qSin((startAngle + spanAngle / 2) * M_PI / 180));

        painter.drawText(labelPoint, item.first + ": " + QString::number(item.second));

        startAngle += spanAngle;
    }
}

void MainWindow::on_suivie_des_absences_clicked()
{
    // Retrieve the model with absent technicians
        QSqlQueryModel *model = tech.getAbsentTechniciens();

        // Set the model to the table view
        ui->tableabsence->setModel(model);
}


void MainWindow::on_notification_clicked()
{
    }



void MainWindow::on_modeButton_clicked()
{
    // Inverser l'état du mode (jour/nuit)
    isNightMode = !isNightMode;

    // Appliquer le style en fonction du mode
    if (isNightMode) {
        qApp->setStyleSheet(
                    "QWidget { background-color: black;color: white;}"
                                "QPushButton { background-color: #333; color: white; border: 1px solid #555; }"
                                "QLineEdit { background-color: #444; color: white; border: 1px solid #666; }"
                                "QTableWidget { background-color: black; color: white; }"
                                "QTableWidget::item { border-bottom: 1px solid #555; }"
                                "QHeaderView::section { background-color: #333; border: 1px solid #555; }" // Header with dark background but keeping text readable
        );
    } else {
        qApp->setStyleSheet(
                    "QWidget { background-color: white;color: black; }"
                                "QPushButton { background-color: #f0f0f0; color: black; border: 1px solid #ccc; }"
                                "QLineEdit { background-color: #fff; color: black; border: 1px solid #ccc; }"
                                "QTableWidget { background-color: white; color: black; }"
                                "QTableWidget::item { border-bottom: 1px solid #ccc; }"
                                "QHeaderView::section { background-color: #f0f0f0; border: 1px solid #ccc; }" // Header with light background
        );
    }
}



void MainWindow::on_afficherCarte_clicked()
{

    bool ok;
    QString idText = ui->idtechrecherche_2->text().trimmed();

    // Vérification plus stricte de l'ID
    if (idText.isEmpty()) {
        QMessageBox::warning(this,
            "Erreur de saisie",
            "Veuillez saisir un ID de technicien.");
        ui->idtechrecherche_2->setFocus();
        return;
    }

    // Conversion sécurisée de l'ID en entier
    int idTech = idText.toInt(&ok);
    if (!ok || idTech <= 0) {
        QMessageBox::warning(this,
            "Erreur de saisie",
            "L'ID doit être un nombre entier positif valide.");
        ui->idtechrecherche_2->setFocus();
        ui->idtechrecherche_2->selectAll();
        return;
    }

    // Curseur d'attente pendant la recherche
    QApplication::setOverrideCursor(Qt::WaitCursor);

    try {
        // Recherche du technicien
        technicien tech = tech.findById(idTech);

        // Restaurer le curseur
        QApplication::restoreOverrideCursor();

        // Vérification des informations du technicien
        if (tech.getNom().isEmpty()) {
            QMessageBox::warning(this,
                "Technicien introuvable",
                QString("Aucun technicien trouvé avec l'ID %1").arg(QString::number(idTech)));
            return;
        }

        // Récupération et validation de l'adresse
        QString adresse = tech.getadresse().trimmed();
        if (adresse.isEmpty()) {
            QMessageBox::warning(this,
                "Données manquantes",
                QString("Le technicien %1 %2 (ID: %3) n'a pas d'adresse enregistrée.")
                    .arg(tech.getNom())
                    .arg(tech.getPrenom())
                    .arg(QString::number(idTech)));
            return;
        }

        // Construction de l'URL en évitant l'ambiguïté
        QString encodedAddress = QUrl::toPercentEncoding(adresse);
        QString urlString = "https://www.google.com/maps/search/?api=1&query=" + encodedAddress;
        QUrl url(urlString);

        if (!url.isValid()) {
            QMessageBox::critical(this,
                "Erreur",
                "Impossible de construire l'URL avec l'adresse fournie.");
            return;
        }

        // Demander confirmation avant d'ouvrir le navigateur
        QString confirmMessage = QString("Voulez-vous afficher l'adresse de %1 %2 sur Google Maps ?\n\nAdresse : %3")
            .arg(tech.getNom())
            .arg(tech.getPrenom())
            .arg(adresse);

        QMessageBox::StandardButton reply = QMessageBox::question(this,
            "Confirmation",
            confirmMessage,
            QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // Tentative d'ouverture du navigateur
            if (!QDesktopServices::openUrl(url)) {
                QMessageBox::critical(this,
                    "Erreur",
                    "Impossible d'ouvrir le navigateur. Veuillez vérifier votre configuration système.");
            }
        }
    }
    catch (const std::exception& e) {
        QApplication::restoreOverrideCursor();
        QMessageBox::critical(this,
            "Erreur système",
            QString("Une erreur est survenue lors de la recherche : %1").arg(QString::fromUtf8(e.what())));
    }
}

void MainWindow::on_idTechDoc_textChanged()
{
    QString idText = ui->idTechDoc->text().trimmed();
    if (!idText.isEmpty()) {
        bool ok;
        int idTech = idText.toInt(&ok);
        if (ok) {
            chargerDocuments(idTech);
        }
    }
}

void MainWindow::on_ajouterDocument_clicked()
{
    // Vérifier l'ID du technicien
    bool ok;
    int idTech = ui->idTechDoc->text().trimmed().toInt(&ok);
    if (!ok || idTech <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID de technicien valide.");
        return;
    }

    // Vérifier si le technicien existe
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT nom FROM technicien WHERE id = :id");
    checkQuery.bindValue(":id", idTech);

    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::warning(this, "Erreur", "Aucun technicien trouvé avec cet ID.");
        return;
    }

    // Vérifier le type de document
    QString type = ui->typeDocument->text().trimmed();
    if (type.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez spécifier le type de document.");
        return;
    }

    // Sélectionner le fichier
    QString fileName = QFileDialog::getOpenFileName(this, "Sélectionner un document", "", "Tous les fichiers (*.*)");
    if (fileName.isEmpty())
        return;

    // Générer un nouveau nom de fichier unique
    QFileInfo fileInfo(fileName);
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString newFileName = QString("%1_%2_%3.%4")
                              .arg(idTech)
                              .arg(fileInfo.baseName())
                              .arg(timestamp)
                              .arg(fileInfo.suffix());

    // Copier le fichier
    QString destination = documentPath + newFileName;
    if (QFile::copy(fileName, destination)) {
        // Generate a unique ID for the document
        QSqlQuery seqQuery;
        seqQuery.exec("SELECT documents_seq.NEXTVAL FROM DUAL");
        if (!seqQuery.next()) {
            QMessageBox::critical(this, "Erreur", "Impossible de générer un ID unique.");
            QFile::remove(destination);
            return;
        }
        int newId = seqQuery.value(0).toInt();

        // Sauvegarder dans la base de données
        QSqlQuery query;
        query.prepare("INSERT INTO documents (id, tech_id, nom_fichier, type, date_ajout, chemin) "
                      "VALUES (:id, :tech_id, :nom_fichier, :type, SYSDATE, :chemin)");
        query.bindValue(":id", newId);
        query.bindValue(":tech_id", idTech);
        query.bindValue(":nom_fichier", fileInfo.fileName());
        query.bindValue(":type", type);
        query.bindValue(":chemin", destination);

        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Document ajouté avec succès.");
            chargerDocuments(idTech);
        } else {
            QMessageBox::warning(this, "Erreur", "Erreur lors de l'enregistrement: " + query.lastError().text());
            QFile::remove(destination);
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la copie du fichier.");
    }
}


void MainWindow::on_supprimerDocument_clicked()
{
    bool ok;
    int idTech = ui->idTechDoc->text().trimmed().toInt(&ok);
    if(!ok || idTech <= 0) {
        QMessageBox::warning(this, "Erreur",
            "Veuillez entrer un ID de technicien valide.");
        return;
    }

    if(!ui->documentsTable->currentItem()) {
        QMessageBox::warning(this, "Erreur",
            "Veuillez sélectionner un document à supprimer.");
        return;
    }

    int row = ui->documentsTable->currentRow();
    QString fileName = ui->documentsTable->item(row, 0)->text();

    if(QMessageBox::question(this, "Confirmation",
        "Voulez-vous vraiment supprimer ce document ?",
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {

        QSqlQuery query;
        query.prepare("DELETE FROM documents WHERE tech_id = ? AND nom_fichier = ?");
        query.addBindValue(idTech);
        query.addBindValue(fileName);

        if(query.exec()) {
            QFile::remove(documentPath + fileName);
            chargerDocuments(idTech);
            QMessageBox::information(this, "Succès",
                "Document supprimé avec succès.");
        } else {
            QMessageBox::warning(this, "Erreur",
                "Erreur lors de la suppression du document.");
        }
    }
}
void MainWindow::on_visualiserDocument_clicked()
{
    if (!ui->documentsTable->currentItem()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un document à visualiser.");
        return;
    }

    int row = ui->documentsTable->currentRow();
    QString fileName = ui->documentsTable->item(row, 0)->text();

    // Ensure proper construction of the file path
    QString filePath = QDir(documentPath).filePath(fileName);

    // Debugging logs
    qDebug() << "documentPath:" << documentPath;
    qDebug() << "fileName:" << fileName;
    qDebug() << "Constructed filePath:" << filePath;

    // Check if the file exists
    if (!QFile::exists(filePath)) {
        QMessageBox::warning(this, "Erreur", QString("Le fichier n'existe pas à l'emplacement spécifié:\n%1").arg(filePath));
        return;
    }

    // Attempt to open the file
    if (!QDesktopServices::openUrl(QUrl::fromLocalFile(filePath))) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le document. Vérifiez votre configuration système.");
    }
}



void MainWindow::chargerDocuments(int idTech)
{
    ui->documentsTable->setRowCount(0);

    QSqlQuery query;
    query.prepare(
        "SELECT nom_fichier, type, TO_CHAR(date_ajout, 'DD/MM/YYYY HH24:MI:SS'), chemin "
        "FROM documents WHERE tech_id = :tech_id");
    query.bindValue(":tech_id", idTech);

    if(query.exec()) {
        while(query.next()) {
            int row = ui->documentsTable->rowCount();
            ui->documentsTable->insertRow(row);

            // Nom du fichier
            ui->documentsTable->setItem(row, 0,
                new QTableWidgetItem(query.value(0).toString()));

            // Type
            ui->documentsTable->setItem(row, 1,
                new QTableWidgetItem(query.value(1).toString()));

            // Date
            ui->documentsTable->setItem(row, 2,
                new QTableWidgetItem(query.value(2).toString()));

            // Taille
            QFileInfo fileInfo(query.value(3).toString());
            qint64 size = fileInfo.size();
            QString sizeStr;
            if(size < 1024)
                sizeStr = QString::number(size) + " B";
            else if(size < 1024*1024)
                sizeStr = QString::number(size/1024.0, 'f', 1) + " KB";
            else
                sizeStr = QString::number(size/1024.0/1024.0, 'f', 1) + " MB";

            ui->documentsTable->setItem(row, 3, new QTableWidgetItem(sizeStr));
        }
    }

    ui->documentsTable->resizeColumnsToContents();
}




