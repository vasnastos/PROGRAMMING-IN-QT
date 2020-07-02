#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(600,700);
    this->setWindowTitle("ASSIGNMENT 9");
    QIcon ic(":/windowicon.png");
    this->setWindowIcon(ic);
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *label=new QLabel;
    label->setFixedSize(0.96 * width(),0.4 * height());
    QPixmap pix(":/product.png");
    label->setPixmap(pix.scaled(label->width(),label->height()));
    ml->addWidget(label);
    QHBoxLayout *r1=new QHBoxLayout;
    ml->addLayout(r1);
    QPushButton *b=new QPushButton;
    QIcon icb(":/loadicon.png");
    b->setIcon(icb);
    b->setText("LOAD");
    r1->addWidget(b);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
    QIcon icb1(":/exportimage.png");
    QPushButton *b1=new QPushButton;
    b1->setIcon(icb1);
    b1->setText("EXPORT");
    r1->addWidget(b1);
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(exportslot()));
    QIcon icb2(":/show.png");
    QPushButton *b2=new QPushButton;
    b2->setIcon(icb2);
    b2->setText("SHOW");
    r1->addWidget(b2);
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(showtab()));
    tab=new QTableWidget;
    QStringList lst;
    lst<<"DESCRIPTION"<<"QUANTITY"<<"PRICE";
    tab->setColumnCount(lst.size());
    tab->setHorizontalHeaderLabels(lst);
    tab->setFixedWidth(0.96 * width());
    ml->addWidget(tab);
    QIcon icgr(":/piechart.png");
    QPushButton *b3=new QPushButton;
    b3->setText("BY_QUANTITY");
    b3->setIcon(icgr);
    QHBoxLayout *r2=new QHBoxLayout;
    QPushButton *b4=new QPushButton;
    b4->setText("BY_PRICE");
    b4->setIcon(icgr);
    ml->addLayout(r2);
    r2->addWidget(b3);
    r2->addWidget(b4);
    connect(b3,SIGNAL(clicked(bool)),this,SLOT(showquantity()));
    connect(b4,SIGNAL(clicked(bool)),this,SLOT(showprice()));
    chart=new QChart();
    chart->setTitle("View");
    QPen pen(Qt::red);
    chart->setBackgroundPen(pen);
    series=new QPieSeries;
    chart->addSeries(series);
    view=new QChartView(chart);
    ml->addWidget(view);
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadslot()
{
  QString fn=QFileDialog::getOpenFileName(this,"open file",".","txt files (*.txt *.csv)");
  if(fn.size()==0)
  {
      return;
  }
  QFile fp(fn);
  bool ok=fp.open(QIODevice::ReadOnly | QIODevice::Text);
  if(!ok) return;
  QTextStream st(&fp);
  while(!st.atEnd())
  {
      QString line=st.readLine();
      if(line.startsWith("#")) continue;
      if(line.size()==0) continue;
      QStringList data=line.split(",");
      if(data.size()!=3) continue;
      product p;
      p.desc=data[0];
      p.quantiny=data[1].toInt();
      p.price=data[2].toDouble();
      prods.append(p);
  }
  fp.close();
}
void MainWindow::exportslot()
{
 QString fn=QFileDialog::getSaveFileName(this,"save file",".","txt files (*.txt *.csv)");
 if(fn.size()!=0)
 {
     QPixmap pix=tab->grab();
     pix.save(fn,"png");
 }
}
void MainWindow::showprice()
{
    chart->setTitle("PRICE CHART");
    series->clear();
    for(auto &x:prods)
    {
        series->append(x.desc,x.price);
    }
    chart->removeSeries(series);
    chart->addSeries(series);

}
void MainWindow::showquantity()
{
  chart->setTitle("QUANTITY CHART");
  series->clear();
  for(auto &x:prods)
  {
      series->append(x.desc,x.quantiny);
  }
  chart->removeSeries(series);
  chart->addSeries(series);
}
void MainWindow::showtab()
{
    tab->setRowCount(prods.size());
    for(int i=0;i<tab->rowCount();i++)
    {
        tab->setItem(i,0,new QTableWidgetItem(prods[i].desc));
        tab->setItem(i,1,new QTableWidgetItem(QString::number(prods[i].quantiny)));
        tab->setItem(i,2,new QTableWidgetItem(QString::number(prods[i].price)));
    }
}
