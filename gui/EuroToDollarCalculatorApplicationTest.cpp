#include "EuroToDollarCalculatorApplicationTest.h"



TEST_F(EuroToDollarCalculatorApplicationTest, GetSetEuro)
{
    objectUnderTest.set_euro("20");
    EXPECT_EQ(objectUnderTest.get_euro(), "20");
}

TEST_F(EuroToDollarCalculatorApplicationTest, GetSetDollar)
{
  
   
    objectUnderTest.set_dollar("20");
   
    EXPECT_EQ(objectUnderTest.get_dollar(), "20");
  

}

TEST_F(EuroToDollarCalculatorApplicationTest, GetSetRechnenState)
{


    objectUnderTest.set_rechnen_enabled(true);

    EXPECT_EQ(objectUnderTest.is_rechnen_enabled(), true);
    

}



TEST_F(EuroToDollarCalculatorApplicationTest, RechnenButtonClick) {
  auto btn_rechnen = get_btn_rechnen();

  btn_rechnen->setEnabled(true);

    EXPECT_CALL(p,rechnen()).Times(1);
   
    QSignalSpy rechnenSpy(btn_rechnen, SIGNAL(clicked()));

    QTest::mouseClick(btn_rechnen, Qt::LeftButton);
    

    EXPECT_EQ(rechnenSpy.count(), 1);
   

}

TEST_F(EuroToDollarCalculatorApplicationTest, BeendenButtonClick) {
  auto btn_beenden = get_btn_beenden();

  EXPECT_CALL(p, beenden()).Times(1);

  QSignalSpy spy(btn_beenden, SIGNAL(clicked()));

  QTest::mouseClick(btn_beenden, Qt::LeftButton);

  EXPECT_EQ(spy.count(), 1);
}

TEST_F(EuroToDollarCalculatorApplicationTest, EuroTextChanged) {
  auto txt_euro = get_txt_euro();

  EXPECT_CALL(p, update_rechnen_action_state()).Times(1);

  QSignalSpy spy(txt_euro, SIGNAL(textChanged(const QString&)));

  QTest::keyClick(txt_euro,'a');

  EXPECT_EQ(spy.count(), 1);
}
