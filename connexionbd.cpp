 #include "connexionbd.h"
#include <QDebug>
#include <QSqlError>
#include <QMessageBox> // Ajout pour un retour visuel direct

connexionBd::connexionBd() {}

#include "connexionbd.h"

QSqlDatabase& connexionBd::connectBase() {
    static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    static bool configured = false; // Une seule configuration

    // 1️⃣ Si la connexion existe déjà et est ouverte → on la retourne
    if (configured && db.isOpen()) {
        return db;
    }

    // 2️⃣ Première configuration
    if (!configured) {
        db.setHostName("localhost");
        db.setDatabaseName("gestion_stage");  // 🔹 Mets ici le nom exact de ta base
        db.setUserName("root");
        db.setPassword("");
        db.setPort(3306);                     // ⚠️ XAMPP utilise 3306 par défaut
        configured = true;
    }

    // 3️⃣ Tentative d’ouverture
    if (db.open()) {
        qDebug() << " Connexion réussie à la base de données !";
    } else {
        QString errorMsg = " Erreur de connexion MySQL:\n" + db.lastError().text();
        qDebug() << errorMsg;
        QMessageBox::critical(nullptr, "Erreur Base de Données", errorMsg);
    }

    return db;
}

