#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>
#include <QDate>
#include <QString>
#include <QListWidget>
#include <QSplitter>
#include <QStackedWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QStatusBar>
#include <QBrush>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("CoWorkEase");
    setMinimumSize(1100, 700);

    this->setStyleSheet(
        "QMainWindow { background-color: #0d1f1f; }"
        "QWidget { background-color: transparent; }"

        "QLabel { color: #e8e0d4; }"

        "QListWidget { background-color: #142828; border: none; outline: none; }"
        "QListWidget::item { padding: 10px 16px; color: #a8b5b0; font-size: 13px; border-radius: 6px; margin: 2px 8px; }"
        "QListWidget::item:selected { background-color: #c9a84c; color: #0d1f1f; }"
        "QListWidget::item:hover { background-color: #1e3a3a; color: #e8e0d4; }"

        "QTableWidget { background-color: #142828; color: #e8e0d4; border: 1px solid #1e3a3a; border-radius: 8px; }"
        "QTableWidget::item { padding: 10px 8px; color: #e8e0d4; font-size: 13px; border-bottom: 1px solid #1a3232; }"
        "QTableWidget::item:selected { background-color: #c9a84c; color: #0d1f1f; }"
        "QTableWidget::item:hover { background-color: #1e3a3a; }"
        "QHeaderView::section { background-color: #0d1f1f; color: #c9a84c; padding: 10px 8px; border: none; border-bottom: 2px solid #c9a84c; font-size: 11px; font-weight: 600; text-transform: uppercase; letter-spacing: 0.5px; }"

        // PRIMARY BUTTONS - GOLD
        "QPushButton { background-color: #1e3a3a; color: #a8b5b0; border: 1px solid #2a4a4a; border-radius: 6px; padding: 8px 16px; font-size: 13px; font-weight: 500; }"
        "QPushButton#actionBtn { background-color: #c9a84c; color: #0d1f1f; border: none; border-radius: 6px; padding: 8px 16px; font-size: 13px; font-weight: 600; }"
        "QPushButton#actionBtn:hover { background-color: #d4b85a; }"
        "QPushButton#actionBtn:pressed { background-color: #b8983e; }"
        "QPushButton:hover { background-color: #d4b85a; }"
        "QPushButton:pressed { background-color: #b8983e; }"

        // REFRESH BUTTON - DARK
        "QPushButton#refreshBtn { background-color: #1e3a3a; color: #a8b5b0; border: 1px solid #2a4a4a; }"
        "QPushButton#refreshBtn:hover { background-color: #2a4a4a; color: #e8e0d4; }"

        "QStatusBar { background-color: #0d1f1f; color: #8a9e96; font-size: 11px; border-top: 1px solid #1e3a3a; }"

        "QLineEdit { background-color: #142828; color: #e8e0d4; border: 1px solid #1e3a3a; border-radius: 6px; padding: 8px 12px; font-size: 13px; }"
        "QLineEdit:focus { border: 2px solid #c9a84c; }"

        "QComboBox { background-color: #142828; color: #e8e0d4; border: 1px solid #1e3a3a; border-radius: 6px; padding: 8px 12px; font-size: 13px; }"
        "QComboBox::drop-down { border: none; }"
        "QComboBox QAbstractItemView { background-color: #142828; color: #e8e0d4; selection-background-color: #c9a84c; selection-color: #0d1f1f; }"

        "QMessageBox { background-color: #142828; color: #e8e0d4; }"
        "QMessageBox QPushButton { min-width: 80px; }"

        "QScrollBar:vertical { background: #0d1f1f; width: 8px; border-radius: 4px; }"
        "QScrollBar::handle:vertical { background: #c9a84c; border-radius: 4px; min-height: 30px; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }"
        "QScrollBar:horizontal { background: #0d1f1f; height: 8px; border-radius: 4px; }"
        "QScrollBar::handle:horizontal { background: #c9a84c; border-radius: 4px; min-width: 30px; }"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { width: 0px; }"
        );

    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(mainSplitter);

    // ===== SIDEBAR =====
    QWidget* sidebar = new QWidget();
    sidebar->setFixedWidth(220);
    sidebar->setStyleSheet("QWidget { background-color: #142828; border-right: 1px solid #1e3a3a; }");
    QVBoxLayout* sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(0, 0, 0, 0);
    sidebarLayout->setSpacing(0);

    // Logo
    QWidget* logoWidget = new QWidget();
    logoWidget->setStyleSheet("QWidget { background-color: #142828; }");
    QVBoxLayout* logoLayout = new QVBoxLayout(logoWidget);
    logoLayout->setContentsMargins(20, 30, 20, 20);
    logoLayout->setSpacing(2);

    QLabel* logoLabel = new QLabel("CoWorkEase");
    logoLabel->setStyleSheet("font-size: 20px; font-weight: 700; color: #c9a84c;");
    QLabel* logoSubLabel = new QLabel("Space Management");
    logoSubLabel->setStyleSheet("font-size: 10px; color: #8a9e96; letter-spacing: 0.5px; text-transform: uppercase;");

    logoLayout->addWidget(logoLabel);
    logoLayout->addWidget(logoSubLabel);
    logoLayout->addStretch();

    navList = new QListWidget();
    navList->addItem("Spaces");
    navList->addItem("Bookings");
    navList->addItem("Members");
    navList->addItem("Revenue");
    navList->setCurrentRow(0);

    // User Info
    QWidget* userWidget = new QWidget();
    userWidget->setStyleSheet("QWidget { background-color: #142828; border-top: 1px solid #1e3a3a; }");
    QHBoxLayout* userLayout = new QHBoxLayout(userWidget);
    userLayout->setContentsMargins(20, 16, 20, 16);
    userLayout->setSpacing(12);

    QLabel* avatarLabel = new QLabel();
    avatarLabel->setFixedSize(36, 36);
    avatarLabel->setStyleSheet(
        "QLabel { background-color: #c9a84c; color: #0d1f1f; border-radius: 18px; font-size: 14px; font-weight: 600; qproperty-alignment: AlignCenter; }"
        );
    avatarLabel->setText("A");

    QWidget* userTextWidget = new QWidget();
    QVBoxLayout* userTextLayout = new QVBoxLayout(userTextWidget);
    userTextLayout->setContentsMargins(0, 0, 0, 0);
    userTextLayout->setSpacing(0);

    QLabel* userNameLabel = new QLabel("Admin");
    userNameLabel->setStyleSheet("font-size: 13px; font-weight: 500; color: #e8e0d4;");
    QLabel* userRoleLabel = new QLabel("Manager");
    userRoleLabel->setStyleSheet("font-size: 11px; color: #8a9e96;");

    userTextLayout->addWidget(userNameLabel);
    userTextLayout->addWidget(userRoleLabel);

    userLayout->addWidget(avatarLabel);
    userLayout->addWidget(userTextWidget);
    userLayout->addStretch();

    sidebarLayout->addWidget(logoWidget);
    sidebarLayout->addWidget(navList);
    sidebarLayout->addWidget(userWidget);

    // ===== CONTENT AREA =====
    QWidget* contentArea = new QWidget();
    QVBoxLayout* contentLayout = new QVBoxLayout(contentArea);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);

    // Top Bar
    QWidget* topBar = new QWidget();
    topBar->setFixedHeight(52);
    topBar->setStyleSheet("QWidget { background-color: #142828; border-bottom: 1px solid #1e3a3a; }");
    QHBoxLayout* topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(32, 0, 32, 0);

    pageTitleLabel = new QLabel("Spaces");
    pageTitleLabel->setStyleSheet("font-size: 15px; font-weight: 500; color: #e8e0d4;");

    QWidget* topBarRight = new QWidget();
    QHBoxLayout* topBarRightLayout = new QHBoxLayout(topBarRight);
    topBarRightLayout->setContentsMargins(0, 0, 0, 0);
    topBarRightLayout->setSpacing(8);

    topRefreshBtn = new QPushButton("Refresh");
    topRefreshBtn->setObjectName("refreshBtn");
    topActionBtn = new QPushButton("+ Add Space");
    topActionBtn->setObjectName("actionBtn");

    topBarRightLayout->addWidget(topRefreshBtn);
    topBarRightLayout->addWidget(topActionBtn);

    topBarLayout->addWidget(pageTitleLabel);
    topBarLayout->addStretch();
    topBarLayout->addWidget(topBarRight);

    // ===== STACKED WIDGET =====
    stackedWidget = new QStackedWidget();
    stackedWidget->setStyleSheet("QStackedWidget { background-color: #0d1f1f; }");

    // ===== SPACES VIEW =====
    QWidget* spacesView = new QWidget();
    QVBoxLayout* spacesViewLayout = new QVBoxLayout(spacesView);
    spacesViewLayout->setContentsMargins(32, 24, 32, 32);
    spacesViewLayout->setSpacing(16);

    spacesCards = createKpiCards({"Total spaces", "0", "Available now", "0", "Avg. rate/hr", "Rs. 0"});
    spacesViewLayout->addWidget(spacesCards);

    spacesTable = new QTableWidget();
    spacesTable->setColumnCount(6);
    spacesTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Rate/hr", "Capacity", "Status"});
    spacesTable->horizontalHeader()->setStretchLastSection(true);
    spacesViewLayout->addWidget(spacesTable);

    // ===== BOOKINGS VIEW =====
    QWidget* bookingsView = new QWidget();
    QVBoxLayout* bookingsViewLayout = new QVBoxLayout(bookingsView);
    bookingsViewLayout->setContentsMargins(32, 24, 32, 32);
    bookingsViewLayout->setSpacing(16);

    bookingsCards = createKpiCards({"Total bookings", "0", "Active", "0", "Cancelled", "0"});
    bookingsViewLayout->addWidget(bookingsCards);

    bookingsTable = new QTableWidget();
    bookingsTable->setColumnCount(8);
    bookingsTable->setHorizontalHeaderLabels({"ID", "Space", "Member", "Date", "Start", "Hours", "Price", "Status"});
    bookingsTable->horizontalHeader()->setStretchLastSection(true);
    bookingsViewLayout->addWidget(bookingsTable);

    // ===== MEMBERS VIEW =====
    QWidget* membersView = new QWidget();
    QVBoxLayout* membersViewLayout = new QVBoxLayout(membersView);
    membersViewLayout->setContentsMargins(32, 24, 32, 32);
    membersViewLayout->setSpacing(16);

    membersCards = createKpiCards({"Total members", "0", "Corporate", "0", "Revenue per member", "Rs. 0"});
    membersViewLayout->addWidget(membersCards);

    membersTable = new QTableWidget();
    membersTable->setColumnCount(5);
    membersTable->setHorizontalHeaderLabels({"ID", "Name", "Phone", "Type", "Total Spent"});
    membersTable->horizontalHeader()->setStretchLastSection(true);
    membersViewLayout->addWidget(membersTable);

    // ===== REVENUE VIEW =====
    QWidget* revenueView = new QWidget();
    QVBoxLayout* revenueViewLayout = new QVBoxLayout(revenueView);
    revenueViewLayout->setContentsMargins(32, 24, 32, 32);
    revenueViewLayout->setSpacing(16);

    revenueCards = createKpiCards({"Total revenue", "Rs. 0", "Active bookings", "0", "Cancelled", "0"});
    revenueViewLayout->addWidget(revenueCards);

    totalRevenueLabel = new QLabel("Total Revenue: Rs. 0");
    totalRevenueLabel->setStyleSheet("font-size: 16px; font-weight: 500; color: #c9a84c;");
    activeBookingsLabel = new QLabel("Active Bookings: 0");
    activeBookingsLabel->setStyleSheet("font-size: 14px; color: #8a9e96;");
    cancelledBookingsLabel = new QLabel("Cancelled Bookings: 0");
    cancelledBookingsLabel->setStyleSheet("font-size: 14px; color: #8a9e96;");

    QFrame* reportFrame = new QFrame();
    reportFrame->setStyleSheet("QFrame { background-color: #142828; border: 1px solid #1e3a3a; border-radius: 8px; padding: 20px; }");
    QVBoxLayout* reportLayout = new QVBoxLayout(reportFrame);
    reportLayout->setContentsMargins(0, 0, 0, 0);
    reportLayout->setSpacing(10);
    reportLayout->addWidget(totalRevenueLabel);
    reportLayout->addWidget(activeBookingsLabel);
    reportLayout->addWidget(cancelledBookingsLabel);

    revenueViewLayout->addWidget(reportFrame);
    revenueViewLayout->addStretch();

    // Add views to stack
    stackedWidget->addWidget(spacesView);
    stackedWidget->addWidget(bookingsView);
    stackedWidget->addWidget(membersView);
    stackedWidget->addWidget(revenueView);

    contentLayout->addWidget(topBar);
    contentLayout->addWidget(stackedWidget);

    mainSplitter->addWidget(sidebar);
    mainSplitter->addWidget(contentArea);
    mainSplitter->setSizes({220, 980});

    // ===== HIDDEN BUTTONS (backward compatibility) =====
    refreshSpacesBtn = new QPushButton();
    refreshBookingsBtn = new QPushButton();
    refreshMembersBtn = new QPushButton();
    refreshReportBtn = new QPushButton();
    bookSpaceBtn = new QPushButton();
    bookSpaceBtn->setObjectName("actionBtn");
    cancelBookingBtn = new QPushButton();
    addMemberBtn = new QPushButton();
    addMemberBtn->setObjectName("actionBtn");
    addSpaceBtn = new QPushButton();
    addSpaceBtn->setObjectName("actionBtn");

    // ===== CONNECTIONS =====
    connect(navList, &QListWidget::currentRowChanged, this, &MainWindow::onNavChanged);
    connect(topRefreshBtn, &QPushButton::clicked, this, &MainWindow::onTopRefresh);
    connect(topActionBtn, &QPushButton::clicked, this, &MainWindow::onTopAction);

    // ===== STATUS BAR =====
    statusLabel = new QLabel("Ready");
    statusBar()->addWidget(statusLabel);
    statusBar()->setStyleSheet("QStatusBar { background-color: #0d1f1f; color: #8a9e96; font-size: 11px; border-top: 1px solid #1e3a3a; }");

    system.loadAllData();
    loadSpacesTable();
    loadBookingsTable();
    loadMembersTable();
    loadRevenueReport();
    updateStatus("System ready");
}

MainWindow::~MainWindow() {
    system.saveAllData();
}

QFrame* MainWindow::createKpiCards(const QStringList& labels) {
    QFrame* container = new QFrame();
    container->setStyleSheet("QFrame { background-color: transparent; border: none; }");
    QHBoxLayout* layout = new QHBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(16);

    for (int i = 0; i < 3; i++) {
        QFrame* card = new QFrame();
        card->setStyleSheet("QFrame { background-color: #142828; border: 1px solid #1e3a3a; border-radius: 8px; padding: 14px 16px; }");
        QVBoxLayout* cardLayout = new QVBoxLayout(card);
        cardLayout->setContentsMargins(0, 0, 0, 0);
        cardLayout->setSpacing(2);

        QLabel* label = new QLabel(labels[i * 2]);
        label->setStyleSheet("font-size: 11px; color: #8a9e96; text-transform: uppercase; letter-spacing: 0.3px;");
        QLabel* value = new QLabel(labels[i * 2 + 1]);
        value->setStyleSheet("font-size: 18px; font-weight: 600; color: #c9a84c;");
        value->setObjectName("kpiValue");

        cardLayout->addWidget(label);
        cardLayout->addWidget(value);
        layout->addWidget(card);
    }
    layout->addStretch();

    return container;
}

void MainWindow::updateKpiCards(int view) {
    int totalSpaces = system.spaces.size();
    int availableSpaces = 0;
    double totalRate = 0;
    for (auto* s : system.spaces) {
        if (!s->getIsBooked()) availableSpaces++;
        totalRate += s->getHourlyRate();
    }
    double avgRate = totalSpaces > 0 ? totalRate / totalSpaces : 0;

    int totalBookings = system.bookings.size();
    int activeBookings = 0;
    int cancelledBookings = 0;
    for (auto& b : system.bookings) {
        if (b.getStatus() == "active") activeBookings++;
        else cancelledBookings++;
    }

    int totalMembers = system.members.size();
    int corporateCount = 0;
    double totalSpent = 0;
    for (auto* m : system.members) {
        if (m->getMemberType() == "Corporate") corporateCount++;
        totalSpent += m->getTotalSpent();
    }
    double avgSpend = totalMembers > 0 ? totalSpent / totalMembers : 0;

    double totalRevenue = 0;
    for (auto& b : system.bookings) {
        if (b.getStatus() == "active") totalRevenue += b.getTotalPrice();
    }

    QList<QLabel*> kpiValues = findChildren<QLabel*>("kpiValue");
    int idx = 0;
    switch (view) {
    case 0:
        if (idx < kpiValues.size()) kpiValues[idx++]->setText(QString::number(totalSpaces));
        if (idx < kpiValues.size()) kpiValues[idx++]->setText(QString::number(availableSpaces));
        if (idx < kpiValues.size()) kpiValues[idx++]->setText("Rs. " + QString::number(avgRate, 'f', 0));
        break;
    case 1:
        if (idx < kpiValues.size()) kpiValues[idx++]->setText(QString::number(totalBookings));
        if (idx < kpiValues.size()) kpiValues[idx++]->setText(QString::number(activeBookings));
        if (idx < kpiValues.size()) kpiValues[idx++]->setText(QString::number(cancelledBookings));
        break;
    case 2:
        if (idx < kpiValues.size()) kpiValues[idx++]->setText(QString::number(totalMembers));
        if (idx < kpiValues.size()) kpiValues[idx++]->setText(QString::number(corporateCount));
        if (idx < kpiValues.size()) kpiValues[idx++]->setText("Rs. " + QString::number(avgSpend, 'f', 0));
        break;
    case 3:
        if (idx < kpiValues.size()) kpiValues[idx++]->setText("Rs. " + QString::number(totalRevenue, 'f', 0));
        if (idx < kpiValues.size()) kpiValues[idx++]->setText(QString::number(activeBookings));
        if (idx < kpiValues.size()) kpiValues[idx++]->setText(QString::number(cancelledBookings));
        break;
    }
}

void MainWindow::onNavChanged(int index) {
    stackedWidget->setCurrentIndex(index);
    QString titles[] = {"Spaces", "Bookings", "Members", "Revenue"};
    pageTitleLabel->setText(titles[index]);
    QString actions[] = {"+ Add Space", "+ Book Space", "+ Add Member", "Refresh"};
    topActionBtn->setText(actions[index]);
    updateKpiCards(index);
}

void MainWindow::onTopRefresh() {
    int idx = stackedWidget->currentIndex();
    switch (idx) {
    case 0: onRefreshSpaces(); break;
    case 1: onRefreshBookings(); break;
    case 2: onRefreshMembers(); break;
    case 3: onRefreshReport(); break;
    }
}

void MainWindow::onTopAction() {
    int idx = stackedWidget->currentIndex();
    switch (idx) {
    case 0: onAddSpace(); break;
    case 1: onBookSpace(); break;
    case 2: onAddMember(); break;
    case 3: onRefreshReport(); break;
    }
}

void MainWindow::loadSpacesTable() {
    spacesTable->setRowCount(system.spaces.size());
    for (size_t i = 0; i < system.spaces.size(); i++) {
        Space* space = system.spaces[i];
        spacesTable->setItem(i, 0, new QTableWidgetItem(QString::number(space->getSpaceID())));
        spacesTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(space->getName())));
        spacesTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(space->getType())));
        spacesTable->setItem(i, 3, new QTableWidgetItem("Rs. " + QString::number(space->getHourlyRate())));
        spacesTable->setItem(i, 4, new QTableWidgetItem(QString::number(space->getCapacity())));

        QTableWidgetItem* statusItem = new QTableWidgetItem(space->getIsBooked() ? "Booked" : "Available");
        if (space->getIsBooked()) {
            statusItem->setBackground(QColor("#3d2b1a"));
            statusItem->setForeground(QBrush(QColor("#d4a84a")));
        } else {
            statusItem->setBackground(QColor("#1a3a3a"));
            statusItem->setForeground(QBrush(QColor("#6ab0a0")));
        }
        spacesTable->setItem(i, 5, statusItem);
    }
    updateKpiCards(0);
}

void MainWindow::loadBookingsTable() {
    bookingsTable->setRowCount(system.bookings.size());
    for (size_t i = 0; i < system.bookings.size(); i++) {
        Booking& booking = system.bookings[i];
        bookingsTable->setItem(i, 0, new QTableWidgetItem(QString::number(booking.getBookingID())));
        bookingsTable->setItem(i, 1, new QTableWidgetItem(QString::number(booking.getSpaceID())));
        bookingsTable->setItem(i, 2, new QTableWidgetItem(QString::number(booking.getMemberID())));
        bookingsTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(booking.getDate())));
        bookingsTable->setItem(i, 4, new QTableWidgetItem(QString::number(booking.getStartHours()) + ":00"));
        bookingsTable->setItem(i, 5, new QTableWidgetItem(QString::number(booking.getDurationHours())));
        bookingsTable->setItem(i, 6, new QTableWidgetItem("Rs. " + QString::number(booking.getTotalPrice())));

        QString statusText = QString::fromStdString(booking.getStatus());
        QTableWidgetItem* statusItem = new QTableWidgetItem(statusText);
        if (statusText == "active") {
            statusItem->setBackground(QColor("#1a3a3a"));
            statusItem->setForeground(QBrush(QColor("#6ab0a0")));
        } else {
            statusItem->setBackground(QColor("#3a1a1a"));
            statusItem->setForeground(QBrush(QColor("#d46a6a")));
        }
        bookingsTable->setItem(i, 7, statusItem);
    }
    updateKpiCards(1);
}

void MainWindow::loadMembersTable() {
    membersTable->setRowCount(system.members.size());
    for (size_t i = 0; i < system.members.size(); i++) {
        Member* member = system.members[i];
        membersTable->setItem(i, 0, new QTableWidgetItem(QString::number(member->getMemberID())));
        membersTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(member->getName())));
        membersTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(member->getPhone())));
        membersTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(member->getMemberType())));
        membersTable->setItem(i, 4, new QTableWidgetItem("Rs. " + QString::number(member->getTotalSpent())));
    }
    updateKpiCards(2);
}

void MainWindow::loadRevenueReport() {
    double totalRevenue = 0;
    int activeBookings = 0;
    int cancelledBookings = 0;
    for (auto& booking : system.bookings) {
        if (booking.getStatus() == "active") {
            totalRevenue += booking.getTotalPrice();
            activeBookings++;
        } else {
            cancelledBookings++;
        }
    }
    totalRevenueLabel->setText("Total Revenue: Rs. " + QString::number(totalRevenue));
    activeBookingsLabel->setText("Active Bookings: " + QString::number(activeBookings));
    cancelledBookingsLabel->setText("Cancelled Bookings: " + QString::number(cancelledBookings));
    updateKpiCards(3);
}

void MainWindow::onRefreshSpaces() { loadSpacesTable(); updateStatus("Spaces refreshed"); }
void MainWindow::onRefreshBookings() { loadBookingsTable(); updateStatus("Bookings refreshed"); }
void MainWindow::onRefreshMembers() { loadMembersTable(); updateStatus("Members refreshed"); }
void MainWindow::onRefreshReport() { loadRevenueReport(); updateStatus("Report refreshed"); }

void MainWindow::onAddSpace() {
    QString name = QInputDialog::getText(this, "Add Space", "Enter Space Name:");
    if (name.isEmpty()) return;

    QStringList types = {"PrivateOffice", "HotDesk", "MeetingRoom"};
    QString type = QInputDialog::getItem(this, "Add Space", "Select Space Type:", types, 0, false);
    if (type.isEmpty()) return;

    double rate = QInputDialog::getDouble(this, "Add Space", "Enter Hourly Rate:", 100, 0, 10000, 2);
    int capacity = QInputDialog::getInt(this, "Add Space", "Enter Capacity:", 1, 1, 50);

    if (type == "PrivateOffice") {
        bool hasLock = QMessageBox::question(this, "Add Space", "Has Lock?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
        bool hasWindow = QMessageBox::question(this, "Add Space", "Has Window?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
        system.spaces.push_back(new PrivateOffice(system.nextSpaceID++, name.toStdString(), rate, capacity, hasLock, hasWindow));
    } else if (type == "HotDesk") {
        bool hasPower = QMessageBox::question(this, "Add Space", "Has Power Outlet?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
        int deskNum = QInputDialog::getInt(this, "Add Space", "Enter Desk Number:", 1, 1, 999);
        system.spaces.push_back(new HotDesk(system.nextSpaceID++, name.toStdString(), rate, capacity, hasPower, deskNum));
    } else if (type == "MeetingRoom") {
        bool hasProjector = QMessageBox::question(this, "Add Space", "Has Projector?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
        bool hasWhiteboard = QMessageBox::question(this, "Add Space", "Has Whiteboard?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
        int maxSeats = QInputDialog::getInt(this, "Add Space", "Enter Max Seats:", 2, 2, 50);
        system.spaces.push_back(new MeetingRoom(system.nextSpaceID++, name.toStdString(), rate, capacity, hasProjector, hasWhiteboard, maxSeats));
    }

    QMessageBox::information(this, "Success", "Space added successfully!");
    onRefreshSpaces();
}

void MainWindow::onBookSpace() {
    if (system.spaces.empty()) {
        QMessageBox::warning(this, "Error", "No spaces available! Please add a space first.");
        return;
    }
    if (system.members.empty()) {
        QMessageBox::warning(this, "Error", "No members available! Please add a member first.");
        return;
    }

    int spaceID = QInputDialog::getInt(this, "Book Space", "Enter Space ID:");
    int memberID = QInputDialog::getInt(this, "Book Space", "Enter Member ID:");
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    int startHour = QInputDialog::getInt(this, "Book Space", "Enter Start Hour (9-21):", 9, 9, 21);
    int duration = QInputDialog::getInt(this, "Book Space", "Enter Duration (1-8 hours):", 1, 1, 8);

    Space* space = system.findSpaceByID(spaceID);
    Member* member = system.findMemberByID(memberID);

    if (!space) {
        QMessageBox::warning(this, "Error", "Space not found!");
        return;
    }
    if (!member) {
        QMessageBox::warning(this, "Error", "Member not found!");
        return;
    }

    bool available = true;
    for (auto& booking : system.bookings) {
        if (booking.getStatus() != "cancelled" &&
            booking.getSpaceID() == spaceID &&
            booking.getDate() == date.toStdString()) {
            int bookedStart = booking.getStartHours();
            int bookedEnd = bookedStart + booking.getDurationHours();
            int newEnd = startHour + duration;
            if ((startHour < bookedEnd && newEnd > bookedStart)) {
                available = false;
                break;
            }
        }
    }

    if (!available) {
        QMessageBox::warning(this, "Error", "Space already booked for that time!");
        return;
    }

    double basePrice = space->calculatePrice(duration);
    double finalPrice = member->applyDiscount(basePrice);

    system.nextBookingID++;
    Booking newBooking(system.nextBookingID, spaceID, memberID, date.toStdString(), startHour, duration, finalPrice);
    system.bookings.push_back(newBooking);

    space->markBooked(true);
    member->addToSpent(finalPrice);

    QMessageBox::information(this, "Success", "Booking Successful!\nBooking ID: " + QString::number(system.nextBookingID) + "\nTotal Price: Rs. " + QString::number(finalPrice));
    onRefreshBookings();
    onRefreshSpaces();
}

void MainWindow::onCancelBooking() {
    if (system.bookings.empty()) {
        QMessageBox::warning(this, "Error", "No bookings to cancel!");
        return;
    }

    int bookingID = QInputDialog::getInt(this, "Cancel Booking", "Enter Booking ID to cancel:");
    Booking* booking = system.findBookingByID(bookingID);
    if (!booking) {
        QMessageBox::warning(this, "Error", "Booking not found!");
        return;
    }
    if (booking->getStatus() == "cancelled") {
        QMessageBox::warning(this, "Error", "Booking already cancelled!");
        return;
    }

    time_t now = time(nullptr);
    int year, month, day;
    sscanf(booking->getDate().c_str(), "%d-%d-%d", &year, &month, &day);

    tm bookingTm = {};
    bookingTm.tm_year = year - 1900;
    bookingTm.tm_mon = month - 1;
    bookingTm.tm_mday = day;
    bookingTm.tm_hour = booking->getStartHours();
    bookingTm.tm_min = 0;
    bookingTm.tm_sec = 0;

    time_t bookingTime = mktime(&bookingTm);
    double secondsDiff = difftime(bookingTime, now);
    double hoursUntilBooking = secondsDiff / 3600.0;

    bool refundApplicable = false;
    double refundAmount = 0;

    if (hoursUntilBooking > 24) {
        refundApplicable = true;
        refundAmount = booking->getTotalPrice();
        QMessageBox::information(this, "Cancelled", "Booking cancelled!\nRefund of Rs. " + QString::number(refundAmount) + " issued.");
    } else if (hoursUntilBooking > 0 && hoursUntilBooking <= 24) {
        QMessageBox::information(this, "Cancelled", "Booking cancelled!\nNo refund (less than 24 hours notice).");
    } else {
        QMessageBox::warning(this, "Error", "Cannot cancel past bookings!");
        return;
    }

    booking->setStatus("cancelled");

    Space* space = system.findSpaceByID(booking->getSpaceID());
    if (space) space->markBooked(false);

    if (refundApplicable) {
        Member* member = system.findMemberByID(booking->getMemberID());
        if (member) {
            member->addToSpent(-refundAmount);
        }
    }

    onRefreshBookings();
    onRefreshSpaces();
}

void MainWindow::onAddMember() {
    QString name = QInputDialog::getText(this, "Add Member", "Enter Name:");
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Name cannot be empty!");
        return;
    }

    QString phone = QInputDialog::getText(this, "Add Member", "Enter Phone:");
    if (phone.isEmpty()) { phone = "00000000000"; }

    QStringList types = {"Daily", "Monthly", "Corporate"};
    QString type = QInputDialog::getItem(this, "Add Member", "Select Member Type:", types, 0, false);
    if (type.isEmpty()) { return; }

    QString joinDate = QDate::currentDate().toString("yyyy-MM-dd");

    if (type == "Daily") {
        system.members.push_back(new DailyMember(system.nextMemberID++, name.toStdString(), phone.toStdString(), joinDate.toStdString()));
    } else if (type == "Monthly") {
        double fee = QInputDialog::getDouble(this, "Add Member", "Enter Monthly Fee:", 1000, 0, 100000, 2);
        system.members.push_back(new MonthlyMember(system.nextMemberID++, name.toStdString(), phone.toStdString(), joinDate.toStdString(), fee));
    } else if (type == "Corporate") {
        QString company = QInputDialog::getText(this, "Add Member", "Enter Company Name:");
        int seats = QInputDialog::getInt(this, "Add Member", "Enter Included Seats:", 1, 1, 100);
        system.members.push_back(new CorporateMember(system.nextMemberID++, name.toStdString(), phone.toStdString(), joinDate.toStdString(), company.toStdString(), seats));
    }

    QMessageBox::information(this, "Success", "Member added!\nMember ID: " + QString::number(system.nextMemberID - 1));
    onRefreshMembers();
}

void MainWindow::updateStatus(const QString& message) {
    statusLabel->setText(message);
}