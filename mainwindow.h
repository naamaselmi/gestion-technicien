#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "technicien.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QPainter>
#include <QVector>

namespace Ui {
class MainWindow;
}

class PieChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PieChartWidget(QWidget *parent = nullptr);
    void setData(const QVector<QPair<QString, int>> &data);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPair<QString, int>> chartData; // Store the data as pairs (name, value)
    QRegularExpression adresseRegex;

};




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_ajouter_clicked();
    void on_supprimer_clicked();
    void on_miseajour_clicked();
    void on_conversionenpdf_clicked();
    void on_statistique_clicked();
    void on_recherche_clicked();
    void on_trier_clicked();
    void on_notification_clicked();
    void on_suivie_des_absences_clicked();
    void on_afficher_clicked();
    void on_exportExcel_clicked();
    void on_modeButton_clicked();
    void on_afficherCarte_clicked();
    void on_ajouterDocument_clicked();
    void on_supprimerDocument_clicked();
    void on_visualiserDocument_clicked();
    void on_idTechDoc_textChanged();

    void on_trier_nom_clicked();

    void on_trier_absence_clicked();

private:
    Ui::MainWindow *ui;
    technicien tech;
    PieChartWidget *pieChartWidget;
    bool isNightMode = false;
    QTableWidget* documentsTable;
    QLineEdit* typeDocument;       // On utilise un simple LineEdit au lieu d'un ComboBox
    QString documentPath;
    void setupDocumentsUI();
    void chargerDocuments(int idTech);
};

#endif // MAINWINDOW_H
