#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QStackedWidget>
#include <QSplitter>
#include <QFrame>
#include <QStatusBar>
#include "CoWorkingSystem.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    CoWorkingSystem system;

    // Sidebar
    QListWidget* navList;
    QLabel* pageTitleLabel;
    QPushButton* topActionBtn;
    QPushButton* topRefreshBtn;

    // KPI Cards
    QFrame* spacesCards;
    QFrame* bookingsCards;
    QFrame* membersCards;
    QFrame* revenueCards;

    // Tables
    QTableWidget* spacesTable;
    QTableWidget* bookingsTable;
    QTableWidget* membersTable;

    // Revenue
    QLabel* totalRevenueLabel;
    QLabel* activeBookingsLabel;
    QLabel* cancelledBookingsLabel;

    // Stacked widget
    QStackedWidget* stackedWidget;
    QLabel* statusLabel;

    // Hidden buttons (backward compatibility)
    QPushButton* refreshSpacesBtn;
    QPushButton* refreshBookingsBtn;
    QPushButton* refreshMembersBtn;
    QPushButton* refreshReportBtn;
    QPushButton* bookSpaceBtn;
    QPushButton* cancelBookingBtn;
    QPushButton* addMemberBtn;
    QPushButton* addSpaceBtn;

private slots:
    void onRefreshSpaces();
    void onRefreshBookings();
    void onRefreshMembers();
    void onRefreshReport();
    void onBookSpace();
    void onCancelBooking();
    void onAddMember();
    void onAddSpace();
    void onNavChanged(int index);
    void onTopRefresh();
    void onTopAction();
    void updateStatus(const QString& message);

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void loadSpacesTable();
    void loadBookingsTable();
    void loadMembersTable();
    void loadRevenueReport();

    QFrame* createKpiCards(const QStringList& labels);
    void updateKpiCards(int view);
};

#endif