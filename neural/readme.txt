* kokkuvote:
 * loob kuhja nodeide systeeme
 * iga systeem on eraldi instance classist
 * igal sammul:
  * vorreldakse systeemide fitnesse
  * systeemid jarjestatakse
  * 1/2 halvimaid systeeme havitatakse
  * esimesest poolest luuakse koopiad, keda muteeritakse
  * uutel systeemidel on x% voimalust et toimub suvaline muteering
  * uutel systeemidel on y% voimalust et talle leitakse paariline ja nad paaritatakse

* funktsioonid yksiku systeemi classis:
 * init:
  * sisend:
   * sisendnodeide kogus
   * valjundnodeide kogus
   * kihtide kogus
   * algne nodeide kogus kihis
  * tegevus:
   * loob algse nodeide systeemi

 * random muudatus:
  * sisend:
   * nodeide tekkimise/sureminse kogus
   * lihaste muutuste delta
  * tegevus:
   * muudab suvaliselt mingi koguse lihaste masse
   * tapab/elustab mingi koguse nodee

 * juhitud muudatus:
  * sisend:
   * tapetavate nodeide loend
   * elustatavate nodeide loend
   * muudetavate lihaste loend
  * tegevus:
   * kasutadatakse systeemide ristamisel
   * muudetakse systeemi lihaste masse vastavalt nouetele
   * tapetakse/elustatakse nodee vastavalt nouetele
   * kui:
    * muudetavat lihast ei eksisteeri
    * tapetavad nodei ei eksisteeri
    * elustatav node juba eksistterib
   -siis ignoreeritakse kasku

 * fitness testi samm:
  * sisend:
   * koigi sisendnodeide vaartused
  * valjund:
   * koigi valjundnodeide vaartused
  * tegevus:
   * arvutatakse valjund systeemi kaudu

* funktsioonid kogu vargi classis:
 * init:
  * sisend:
   *