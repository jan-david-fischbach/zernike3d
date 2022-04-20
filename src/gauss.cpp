/** \file gauss.hpp
  Implementation of gauss.hpp.
  \author J. Houdayer
*/

#include <cmath>
#include "gauss.hpp"

double gauss_scheme::check_weights() const
{
  double sum = 0;
  for (auto &i: data)
    sum += i.weight;

  return fabs(sum - 1);
}

double gauss_scheme::check_poly() const
{
  double sum = 0;
  for (auto &i: data)
    sum += i.weight * pow(i.x, order);

  return fabs(sum - 1. / (order + 1));
}


int gauss_scheme::check_sorted() const
{
  double w = 0;
  int k = 0;
  for (auto &i: data) {
    if (i.weight < w) return k;
    w = i.weight;
    k++;
  }
  return -1;
}

std::ostream &operator <<(std::ostream &os, const gauss_scheme &s)
{
  double sum = 0, v;
  os << "gauss quadrature, order " << s.order << ", size " << s.data.size() << ": ";
  sum += v = s.check_weights();
  os << ", weights " << v;
  sum += v = s.check_poly();
  os << ", exactness " << v;
  int k = s.check_sorted();
  os << ", sorted " << k;
  bool ok = sum < 1e-12 && k==-1;
  if (ok)
    os << ", \033[0;32mOK\033[0m" << std::endl;
  else
    os << ", \033[0;31mBAD\033[0m" << std::endl;
  return os;
}

const gauss_scheme &gauss_selector::get_scheme(int n) const
{
  for (auto &s: schemes)
    if (s.order >= n)
      return s;
  return schemes.back();
}

int gauss_selector::max_order() const
{
  return schemes.back().order;
}

#define N1(x, w) {x, w}
#define N2(x, w) N1(x, w), N1(1 - x, w)

gauss_selector::gauss_selector()
{
  const std::vector<gauss_point> data2 =
  {
    N2(0.211324865405187,0.5)
  };

  const std::vector<gauss_point> data3 =
  {
    N2(0.112701665379258,0.277777777777778),
    N1(0.5,0.444444444444444)
  };

  const std::vector<gauss_point> data4 =
  {
    N2(0.069431844202974,0.173927422568727),
    N2(0.33000947820757,0.326072577431273)
  };
  
  const std::vector<gauss_point> data6 =
  {
    N2(0.033765242898424,0.085662246189585),
    N2(0.16939530676687,0.180380786524069),
    N2(0.3806904069584,0.233956967286346)
  };
  
  const std::vector<gauss_point> data8 =
  {
    N2(0.019855071751232,0.0506142681451881),
    N2(0.10166676129319,0.111190517226687),
    N2(0.23723379504184,0.156853322938944),
    N2(0.40828267875218,0.181341891689181)
  };

  const std::vector<gauss_point> data11 =
  {
    N2(0.010885670926972,0.0278342835580868),
    N2(0.05646870011595,0.0627901847324523),
    N2(0.13492399721298,0.0931451054638671),
    N2(0.24045193539659,0.116596882295995),
    N2(0.3652284220238,0.131402272255123),
    N1(0.5,0.13646254338895)
  };
  
  const std::vector<gauss_point> data16 =
  {
    N2(0.005299532504175,0.013576229705877),
    N2(0.02771248846338,0.0311267619693239),
    N2(0.06718439880608,0.0475792558412464),
    N2(0.1222977958225,0.062314485627767),
    N2(0.1910618777987,0.074797994408288),
    N2(0.2709916111714,0.084578259697501),
    N2(0.3591982246104,0.091301707522462),
    N2(0.4524937450812,0.094725305227534)
  };

  const std::vector<gauss_point> data23 =
  {
    N2(0.002615332501224,0.00670592974357089),
    N2(0.01372876439094,0.0154940029284897),
    N2(0.03351445658699,0.0240188358655423),
    N2(0.06162382086478,0.0321162107042629),
    N2(0.0975557991906,0.0396407058883595),
    N2(0.140669318434,0.0464578830300176),
    N2(0.1901950621182,0.0524460457322707),
    N2(0.245249261077,0.0574983201112057),
    N2(0.3048494809849,0.0615245421533648),
    N2(0.3679321595148,0.0644528610940411),
    N2(0.4333715878508,0.0662310197023483),
    N1(0.5,0.066827286093053)
  };

  const std::vector<gauss_point> data32 =
  {
    N2(0.001368069075259,0.00350930500473505),
    N2(0.00719424422737,0.0081371973654528),
    N2(0.01761887220625,0.012696032654631),
    N2(0.03254696203113,0.0171369314565107),
    N2(0.051839422117,0.0214179490111133),
    N2(0.0753161931337,0.0254990296311881),
    N2(0.102758102016,0.0293420467392678),
    N2(0.1339089406299,0.0329111113881809),
    N2(0.1684778665349,0.0361728970544243),
    N2(0.2061421213796,0.0390969478935352),
    N2(0.2465500455339,0.0416559621134734),
    N2(0.2893243619347,0.0438260465022019),
    N2(0.3340656988589,0.0455869393478819),
    N2(0.3803563188739,0.0469221995404023),
    N2(0.427764019209,0.047819360039637),
    N2(0.475846167156,0.048270044257364)
  };

  const std::vector<gauss_point> data45 =
  {
    N2(0.000698177409032,0.00179133157764178),
    N2(0.0036750007764,0.00416159464810912),
    N2(0.00901564248273,0.00651555249579139),
    N2(0.01669584480155,0.0088387676289688),
    N2(0.0266791545022,0.0111199237752894),
    N2(0.0389180316405,0.0133481069837888),
    N2(0.0533541641234,0.0155126874672577),
    N2(0.0699187620197,0.0176033461008045),
    N2(0.088532889749,0.0196101183646512),
    N2(0.109107843703,0.0215234403545825),
    N2(0.1315455755273,0.0233341938591867),
    N2(0.1557391596144,0.025033749618976),
    N2(0.1815733027734,0.0266140083656345),
    N2(0.2089248937153,0.0280674393798932),
    N2(0.237663589769,0.0293871163594209),
    N2(0.26765243804,0.0305667504155333),
    N2(0.298748528071,0.03160072003691),
    N2(0.330803672875,0.0324840978753617),
    N2(0.363665115124,0.0332126742249213),
    N2(0.397176255108,0.0337829770818038),
    N2(0.431177397008,0.0341922886893348),
    N2(0.465506509918,0.0344386584888307),
    N1(0.5,0.034520912414616)
  };
  
  const std::vector<gauss_point> data63 =
  {
    N2(0.000358507985438,0.000919937297788542),
    N2(0.00188799361101,0.00213925417343188),
    N2(0.00463572655391,0.00335514588298007),
    N2(0.00859559470314,0.00456298433816333),
    N2(0.0137579826512,0.00575968803844002),
    N2(0.0201102751205,0.00694230630805781),
    N2(0.0276369329795,0.00810793920516917),
    N2(0.0363195396891,0.00925373223008064),
    N2(0.0461368486107,0.0103768806290195),
    N2(0.0570648357461,0.011474635502445),
    N2(0.0690767588179,0.0125443102766725),
    N2(0.0821432228402,0.013583287179549),
    N2(0.0962322521133,0.0145890236041403),
    N2(0.111309368505,0.0155590583111099),
    N2(0.127337675841,0.0164910174418897),
    N2(0.144277950208,0.0173826203226779),
    N2(0.162088735943,0.0182316850427286),
    N2(0.180726447089,0.0190361337921748),
    N2(0.200145474061,0.019793997945772),
    N2(0.220298295257,0.0205034228798332),
    N2(0.241135593355,0.0211626725104079),
    N2(0.262606376003,0.0217701335415138),
    N2(0.284658100602,0.0223243194129707),
    N2(0.307236802894,0.0228238739381463),
    N2(0.330287229013,0.0232675746226918),
    N2(0.353752970707,0.0236543356561345),
    N2(0.377576603377,0.0239832105689976),
    N2(0.401699826604,0.0242533945489419),
    N2(0.426063606821,0.024464226410256),
    N2(0.450608321777,0.0246151902118738),
    N2(0.475273906442,0.0247059165199591),
    N1(0.5,0.024736183311966)
  };

  const std::vector<gauss_point> data89 =
  {
    N2(0.000180480567733,0.000463143552596736),
    N2(0.00095069714486,0.00107755629110956),
    N2(0.00233537979663,0.00169155239620373),
    N2(0.00433313059567,0.00230354367173162),
    N2(0.0069415260694,0.00291271289438505),
    N2(0.0101573617081,0.00351829843549456),
    N2(0.0139766786255,0.00411955126269454),
    N2(0.0183947726717,0.00471572963039895),
    N2(0.0234062013536,0.00530609864498609),
    N2(0.0290047909149,0.00588993079043745),
    N2(0.0351836440881,0.00646650669630134),
    N2(0.0419351486556,0.00703511597432224),
    N2(0.049250986858,0.00759505807233306),
    N2(0.057122145658,0.00814564312739619),
    N2(0.065538927851,0.0086861928107512),
    N2(0.074490964022,0.00921604116089206),
    N2(0.083967225315,0.00973453540257594),
    N2(0.093956037031,0.01024103675020014),
    N2(0.104445093008,0.0107349211942806),
    N2(0.115421470783,0.0112155802699182),
    N2(0.126871647512,0.0116824218062277),
    N2(0.138781516636,0.0121348706557612),
    N2(0.151136405252,0.0125723694030013),
    N2(0.163921092197,0.0129943790510369),
    N2(0.177119826797,0.0134003796855646),
    N2(0.190716348273,0.0137898711153923),
    N2(0.204693905776,0.0141623734886526),
    N2(0.219035279019,0.0145174278839634),
    N2(0.233722799498,0.0148545968758062),
    N2(0.248738372256,0.0151734650734246),
    N2(0.264063498176,0.0154736396325774),
    N2(0.279679296776,0.0157547507395171),
    N2(0.295566529463,0.0160164520665948),
    N2(0.31170562324,0.0162584211989316),
    N2(0.32807669482,0.0164803600316306),
    N2(0.344659575117,0.0166819951370387),
    N2(0.361433834099,0.0168630781016073),
    N2(0.378378805957,0.0170233858319355),
    N2(0.395473614565,0.0171627208296195),
    N2(0.412697199196,0.0172809114345689),
    N2(0.430028340475,0.0173778120364907),
    N2(0.447445686515,0.0174533032542804),
    N2(0.464927779226,0.0175072920830982),
    N2(0.482453080751,0.017539712008951),
    N1(0.5,0.017550523090637)
  };

  const std::vector<gauss_point> data126 =
  {
    N2(0.000090346383798,0.000231851013556082),
    N2(0.00047596851622,0.000539566259311145),
    N2(0.00116948268202,0.00084740466370064),
    N2(0.00217061531604,0.0011547600560591),
    N2(0.0034787678745,0.00146141122601864),
    N2(0.0050931380901,0.00176716348088026),
    N2(0.0070127318334,0.00207182677606636),
    N2(0.0092363658447,0.00237521271357694),
    N2(0.0117626690269,0.00267713398341347),
    N2(0.0145900834784,0.00297740428913751),
    N2(0.017716865527,0.00327583839858412),
    N2(0.0211410868367,0.00357225223328497),
    N2(0.0248606356128,0.00386646297134726),
    N2(0.028873217912,0.00415828915524086),
    N2(0.03317635906,0.0044475508012312),
    N2(0.037767405183,0.00473406950907234),
    N2(0.042643524843,0.00501766857130703),
    N2(0.047801710787,0.00529817308182911),
    N2(0.053238781801,0.0055754100435031),
    N2(0.058951384673,0.0058492084747025),
    N2(0.064935996262,0.006119399514661),
    N2(0.071188925668,0.0063858165275507),
    N2(0.077706316512,0.0066482952052091),
    N2(0.084484149312,0.0069066736684443),
    N2(0.091518243964,0.0071607925668512),
    N2(0.098804262319,0.0074104951770736),
    N2(0.106337710858,0.007655627499451),
    N2(0.114113943463,0.0078960383529875),
    N2(0.122128164285,0.0081315794685847),
    N2(0.130375430698,0.0083621055804802),
    N2(0.138850656351,0.0085874745158344),
    N2(0.147548614304,0.0088075472824113),
    N2(0.156463940247,0.0090221881542969),
    N2(0.165591135817,0.0092312647556053),
    N2(0.174924571981,0.0094346481421175),
    N2(0.184458492512,0.0096322128808049),
    N2(0.194187017538,0.0098238371271868),
    N2(0.204104147167,0.010009402700476),
    N2(0.214203765191,0.0101887951564635),
    N2(0.224479642853,0.0103619038581001),
    N2(0.234925442691,0.0105286220437292),
    N2(0.24553472245,0.01068884689293),
    N2(0.256300939048,0.01084247958993),
    N2(0.267217452617,0.0109894253845478),
    N2(0.27827753059,0.0111295936506281),
    N2(0.28947435188,0.0112628979419341),
    N2(0.30080101103,0.011389256045461),
    N2(0.31225052255,0.0115085900321397),
    N2(0.32381582515,0.0116208263048983),
    N2(0.33548978613,0.011725895644051),
    N2(0.34726520581,0.0118237332499887),
    N2(0.35913482189,0.0119142787831426),
    N2(0.37109131402,0.0119974764011976),
    N2(0.38312730823,0.0120732747935321),
    N2(0.39523538156,0.0121416272128628),
    N2(0.40740806657,0.012202491504075),
    N2(0.41963785596,0.0122558301302215),
    N2(0.43191720725,0.0123016101956723),
    N2(0.44423854737,0.0123398034664027),
    N2(0.45659427735,0.0123703863874059),
    N2(0.46897677702,0.0123933400972203),
    N2(0.48137840971,0.0124086504395619),
    N2(0.49379152691,0.012416307972055)
  };

  const std::vector<gauss_point> data178 =
  {
    N2(0.000045375666854,0.000116446852945617),
    N2(0.0002390662486,0.000271031103643396),
    N2(0.00058746749409,0.000425760371044985),
    N2(0.00109054889694,0.00058037764872092),
    N2(0.0017481641107,0.00073481914797135),
    N2(0.002560111704,0.00088903423311508),
    N2(0.0035261409303,0.00104297439421965),
    N2(0.0046459528701,0.00119659169603289),
    N2(0.0059192008059,0.00134983845402191),
    N2(0.0073454904237,0.00150266715377092),
    N2(0.0089243799717,0.00165503043347929),
    N2(0.0106553804132,0.001806881086176),
    N2(0.0125379555855,0.00195817206899803),
    N2(0.01457152237,0.00210885651527053),
    N2(0.016755450876,0.00225888774778075),
    N2(0.019089064634,0.00240821929257983),
    N2(0.02157164081,0.00255680489301458),
    N2(0.024202410428,0.00270459852384553),
    N2(0.026980558605,0.00285155440537765),
    N2(0.029905224812,0.00299762701756317),
    N2(0.032975503132,0.00314277111405212),
    N2(0.036190442545,0.00328694173617548),
    N2(0.039549047224,0.00343009422684981),
    N2(0.043050276838,0.00357218424439538),
    N2(0.04669304688,0.00371316777626102),
    N2(0.050476229001,0.00385300115265004),
    N2(0.054398651358,0.00399164106004196),
    N2(0.058459098979,0.00412904455460529),
    N2(0.062656314139,0.00426516907549675),
    N2(0.066988996746,0.00439997245804257),
    N2(0.071455804752,0.00453341294679754),
    N2(0.076055354559,0.00466544920847767),
    N2(0.080786221456,0.00479604034476234),
    N2(0.085646940052,0.00492514590496194),
    N2(0.090636004738,0.00505272589854699),
    N2(0.095751870149,0.00517874080753481),
    N2(0.100992951642,0.0053031515987299),
    N2(0.106357625789,0.0054259197358144),
    N2(0.11184423088,0.0055470071912842),
    N2(0.117451067436,0.0056663764582282),
    N2(0.123176398736,0.0057839905619458),
    N2(0.129018451356,0.0058998130713996),
    N2(0.134975415716,0.0060138081105001),
    N2(0.14104544664,0.0061259403692181),
    N2(0.14722666394,0.006236175114522),
    N2(0.15351715298,0.0063444782011362),
    N2(0.15991496527,0.0064508160821179),
    N2(0.16641811909,0.0065551558192479),
    N2(0.17302460008,0.0066574650932334),
    N2(0.17973236188,0.0067577122137186),
    N2(0.18653932677,0.0068558661291015),
    N2(0.19344338627,0.0069518964361513),
    N2(0.20044240185,0.0070457733894262),
    N2(0.20753420556,0.0071374679104871),
    N2(0.21471660071,0.0072269515969045),
    N2(0.22198736256,0.0073141967310563),
    N2(0.22934423898,0.0073991762887132),
    N2(0.23678495116,0.0074818639474096),
    N2(0.24430719436,0.0075622340945968),
    N2(0.25190863854,0.0076402618355767),
    N2(0.25958692916,0.0077159230012129),
    N2(0.26733968787,0.007789194155417),
    N2(0.27516451323,0.0078600526024079),
    N2(0.28305898151,0.0079284763937422),
    N2(0.29102064739,0.0079944443351123),
    N2(0.29904704475,0.0080579359929114),
    N2(0.30713568739,0.008118931700563),
    N2(0.31528406986,0.0081774125646128),
    N2(0.32348966819,0.0082333604705803),
    N2(0.33174994069,0.0082867580885706),
    N2(0.34006232875,0.0083375888786416),
    N2(0.34842425758,0.0083858370959278),
    N2(0.35683313709,0.008431487795517),
    N2(0.36528636261,0.0084745268370795),
    N2(0.37378131576,0.0085149408892482),
    N2(0.38231536521,0.0085527174337479),
    N2(0.39088586755,0.0085878447692729),
    N2(0.39949016805,0.0086203120151115),
    N2(0.40812560152,0.008650109114516),
    N2(0.41678949314,0.0086772268378185),
    N2(0.42547915926,0.008701656785289),
    N2(0.43419190825,0.0087233913897377),
    N2(0.44292504134,0.0087424239188587),
    N2(0.45167585343,0.0087587484773155),
    N2(0.46044163394,0.0087723600085671),
    N2(0.46921966769,0.008783254296434),
    N2(0.47800723565,0.0087914279664046),
    N2(0.48680161589,0.00879687848668),
    N2(0.49560008434,0.008799604168958)
  };
  
  const std::vector<gauss_point> data251 =
  {
    N2(0.000022857425153,0.0000586590873431073),
    N2(0.00012043049436,0.000136538307080575),
    N2(0.00029595595391,0.000214511558309628),
    N2(0.00054944540881,0.00029246135682967),
    N2(0.0008808640827,0.000370367533062168),
    N2(0.001290161404,0.00044821652208308),
    N2(0.0017772738886,0.000525995803276002),
    N2(0.002342125686,0.000603693113453374),
    N2(0.0029846287332,0.000681296278121129),
    N2(0.0037046828161,0.000758793165344131),
    N2(0.0045021756033,0.000836171671412792),
    N2(0.0053769826717,0.000913419716459019),
    N2(0.00632896753,0.000990525243650106),
    N2(0.007357981642,0.00106747621981558),
    N2(0.00846386445,0.0011442606366989),
    N2(0.009646443401,0.00122086651250072),
    N2(0.010905533976,0.00129728189356539),
    N2(0.012240939715,0.00137349485614047),
    N2(0.013652452251,0.00144949350817401),
    N2(0.015139851341,0.00152526599113113),
    N2(0.016702904902,0.00160080048181956),
    N2(0.018341369045,0.00167608519421833),
    N2(0.020054988115,0.0017511083813061),
    N2(0.02184349473,0.00182585833688685),
    N2(0.023706609823,0.00190032339741133),
    N2(0.025644042686,0.00197449194379354),
    N2(0.027655491015,0.00204835240322112),
    N2(0.029740640955,0.0021218932509593),
    N2(0.031899167154,0.00219510301214783),
    N2(0.034130732809,0.00226797026359042),
    N2(0.036434989721,0.00234048363553644),
    N2(0.038811578348,0.00241263181345442),
    N2(0.041260127863,0.00248440353979706),
    N2(0.04378025621,0.00255578761575746),
    N2(0.046371570164,0.00262677290301625),
    N2(0.049033665394,0.00269734832547935),
    N2(0.051766126522,0.00276750287100607),
    N2(0.054568527194,0.00283722559312721),
    N2(0.05744043014,0.002906505612753),
    N2(0.060381387248,0.00297533211987055),
    N2(0.063390939628,0.00304369437523044),
    N2(0.066468617691,0.00311158171202243),
    N2(0.06961394121,0.00317898353753974),
    N2(0.07282641942,0.00324588933483186),
    N2(0.07610555106,0.00331228866434551),
    N2(0.07945082447,0.00337817116555354),
    N2(0.08286171769,0.00344352655857148),
    N2(0.08633769849,0.00350834464576159),
    N2(0.08987822451,0.00357261531332393),
    N2(0.0934827433,0.00363632853287452),
    N2(0.09715069244,0.00369947436301006),
    N2(0.10088149961,0.0037620429508591),
    N2(0.10467458267,0.00382402453361946),
    N2(0.10852934978,0.00388540944008148),
    N2(0.11244519947,0.00394618809213711),
    N2(0.11642152072,0.0040063510062744),
    N2(0.1204576931,0.0040658887950572),
    N2(0.12455308684,0.00412479216858997),
    N2(0.1287070629,0.00418305193596727),
    N2(0.13291897314,0.00424065900670787),
    N2(0.13718816035,0.00429760439217316),
    N2(0.1415139584,0.00435387920696968),
    N2(0.14589569232,0.00440947467033553),
    N2(0.1503326784,0.00446438210751048),
    N2(0.15482422433,0.00451859295108952),
    N2(0.15936962928,0.00457209874235962),
    N2(0.16396818402,0.00462489113261965),
    N2(0.168619171,0.00467696188448298),
    N2(0.17332186453,0.00472830287316285),
    N2(0.17807553082,0.00477890608774005),
    N2(0.18287942815,0.00482876363241294),
    N2(0.18773280694,0.00487786772772945),
    N2(0.1926349099,0.00492621071180092),
    N2(0.19758497214,0.00497378504149761),
    N2(0.20258222129,0.0050205832936257),
    N2(0.2076258776,0.00506659816608555),
    N2(0.2127151541,0.00511182247901107),
    N2(0.21784925668,0.00515624917589002),
    N2(0.22302738427,0.00519987132466506),
    N2(0.22824872888,0.00524268211881538),
    N2(0.23351247582,0.00528467487841877),
    N2(0.23881780377,0.00532584305119389),
    N2(0.24416388492,0.00536618021352264),
    N2(0.2495498851,0.00540568007145247),
    N2(0.25497496391,0.00544433646167847),
    N2(0.26043827485,0.00548214335250501),
    N2(0.26593896548,0.00551909484478691),
    N2(0.27147617749,0.00555518517284992),
    N2(0.27704904689,0.00559040870539032),
    N2(0.28265670413,0.00562475994635363),
    N2(0.28829827423,0.00565823353579215),
    N2(0.29397287691,0.00569082425070132),
    N2(0.29967962674,0.00572252700583465),
    N2(0.30541763328,0.00575333685449723),
    N2(0.31118600121,0.00578324898931754),
    N2(0.31698383047,0.00581225874299759),
    N2(0.32281021639,0.00584036158904117),
    N2(0.32866424988,0.00586755314246012),
    N2(0.3345450175,0.00589382916045855),
    N2(0.34045160165,0.00591918554309486),
    N2(0.34638308072,0.00594361833392146),
    N2(0.35233852919,0.00596712372060212),
    N2(0.3583170178,0.00598969803550679),
    N2(0.36431761372,0.00601133775628393),
    N2(0.37033938066,0.00603203950641007),
    N2(0.376381379,0.00605180005571667),
    N2(0.382442666,0.00607061632089414),
    N2(0.3885222959,0.00608848536597295),
    N2(0.39461932007,0.00610540440278173),
    N2(0.40073278716,0.00612137079138229),
    N2(0.40686174327,0.0061363820404816),
    N2(0.41300523207,0.00615043580782047),
    N2(0.41916229499,0.00616352990053902),
    N2(0.4253319713,0.00617566227551888),
    N2(0.43151329834,0.00618683103970193),
    N2(0.4377053116,0.00619703445038573),
    N2(0.44390704492,0.0062062709154954),
    N2(0.45011753063,0.00621453899383208),
    N2(0.45633579968,0.00622183739529776),
    N2(0.46256088181,0.00622816498109661),
    N2(0.46879180571,0.00623352076391265),
    N2(0.47502759913,0.00623790390806384),
    N2(0.48126728908,0.00624131372963241),
    N2(0.48750990197,0.00624374969657165),
    N2(0.49375446373,0.00624521142878888),
    N1(0.5,0.0062456986982048)
  };

  const std::vector<gauss_point> data501 =
  {
    N2(5.748629451e-6,0.0000147528113031145),
    N2(0.00003028893837,0.0000343411746823),
    N2(0.00007443782691,0.0000539571966001202),
    N2(0.00013820336886,0.0000735736205229972),
    N2(0.0002215842631,0.0000931876630604447),
    N2(0.0003245775244,0.000112798200195237),
    N2(0.0004471792066,0.000132404368425916),
    N2(0.0005893845376,0.000152005366422786),
    N2(0.0007511879553,0.000171600412145465),
    N2(0.0009325831195,0.000191188730794638),
    N2(0.0011335629173,0.000210769550762261),
    N2(0.0013541194648,0.000230342102084639),
    N2(0.0015942441089,0.00024990561579605),
    N2(0.001853927428,0.000269459323643541),
    N2(0.002133159232,0.000289002457959736),
    N2(0.002431928563,0.000308534251609892),
    N2(0.002750223699,0.000328053937975992),
    N2(0.003088032148,0.000347560750960274),
    N2(0.003445340655,0.000367053924999406),
    N2(0.003822135197,0.000386532695084726),
    N2(0.004218400989,0.000405996296786038),
    N2(0.00463412248,0.000425443966277567),
    N2(0.005069283356,0.000444874940365239),
    N2(0.005523866541,0.000464288456514805),
    N2(0.005997854196,0.000483683752880506),
    N2(0.00649122772,0.000503060068334084),
    N2(0.007003967752,0.000522416642494016),
    N2(0.007536054171,0.000541752715754904),
    N2(0.008087466097,0.000561067529316942),
    N2(0.008658181891,0.00058036032521545),
    N2(0.009248179156,0.000599630346350435),
    N2(0.00985743474,0.000618876836516156),
    N2(0.010485924734,0.000638099040430699),
    N2(0.011133624474,0.000657296203765529),
    N2(0.011800508543,0.000676467573175027),
    N2(0.012486550771,0.000695612396326007),
    N2(0.013191724237,0.000714729921927199),
    N2(0.013916001266,0.000733819399758698),
    N2(0.014659353437,0.000752880080701381),
    N2(0.015421751579,0.000771911216766282),
    N2(0.016203165773,0.000790912061123932),
    N2(0.017003565356,0.000809881868133653),
    N2(0.01782291892,0.000828819893372804),
    N2(0.0186611943,0.000847725393665988),
    N2(0.01951835861,0.00086659762711421),
    N2(0.02039437822,0.000885435853123981),
    N2(0.02128921874,0.00090423933243638),
    N2(0.02220284506,0.000923007327156056),
    N2(0.02313522132,0.000941739100780185),
    N2(0.02408631094,0.000960433918227366),
    N2(0.02505607659,0.000979091045866466),
    N2(0.02604448022,0.00099770975154541),
    N2(0.02705148304,0.001016289304619905),
    N2(0.02807704554,0.00103482897598212),
    N2(0.02912112746,0.00105332803808928),
    N2(0.03018368784,0.00107178576499223),
    N2(0.03126468497,0.00109020143236394),
    N2(0.03236407644,0.00110857431752786),
    N2(0.0334818191,0.00112690369948638),
    N2(0.0346178691,0.00114518885894902),
    N2(0.03577218184,0.00116342907836074),
    N2(0.03694471204,0.00118162364193004),
    N2(0.03813541367,0.00119977183565709),
    N2(0.03934424001,0.00121787294736171),
    N2(0.04057114363,0.00123592626671137),
    N2(0.04181607638,0.00125393108524899),
    N2(0.0430789894,0.00127188669642082),
    N2(0.04435983314,0.00128979239560413),
    N2(0.04565855732,0.00130764748013483),
    N2(0.04697511099,0.00132545124933511),
    N2(0.04830944248,0.00134320300454088),
    N2(0.04966149943,0.00136090204912923),
    N2(0.05103122878,0.00137854768854572),
    N2(0.05241857677,0.0013961392303317),
    N2(0.05382348898,0.0014136759841514),
    N2(0.05524591025,0.00143115726181911),
    N2(0.05668578478,0.00144858237732611),
    N2(0.05814305606,0.00146595064686765),
    N2(0.0596176669,0.00148326138886973),
    N2(0.06110955943,0.00150051392401589),
    N2(0.06261867512,0.00151770757527386),
    N2(0.06414495473,0.0015348416679221),
    N2(0.06568833838,0.00155191552957632),
    N2(0.06724876549,0.00156892849021581),
    N2(0.06882617483,0.00158587988220982),
    N2(0.07042050451,0.00160276904034365),
    N2(0.07203169195,0.00161959530184485),
    N2(0.07365967393,0.00163635800640918),
    N2(0.07530438656,0.00165305649622652),
    N2(0.07696576529,0.00166969011600671),
    N2(0.07864374495,0.00168625821300525),
    N2(0.08033825966,0.00170276013704892),
    N2(0.08204924295,0.00171919524056128),
    N2(0.08377662766,0.00173556287858809),
    N2(0.085520346,0.00175186240882265),
    N2(0.08728032956,0.00176809319163095),
    N2(0.08905650926,0.00178425459007681),
    N2(0.0908488154,0.00180034596994686),
    N2(0.09265717765,0.00181636669977546),
    N2(0.09448152504,0.00183231615086941),
    N2(0.09632178598,0.00184819369733269),
    N2(0.09817788826,0.001863998716091),
    N2(0.10004975903,0.00187973058691619),
    N2(0.10193732484,0.00189538869245064),
    N2(0.10384051162,0.00191097241823142),
    N2(0.10575924468,0.0019264811527145),
    N2(0.10769344873,0.00194191428729866),
    N2(0.10964304785,0.00195727121634942),
    N2(0.11160796556,0.00197255133722279),
    N2(0.11358812473,0.00198775405028892),
    N2(0.11558344766,0.00200287875895564),
    N2(0.11759385604,0.00201792486969187),
    N2(0.119619271,0.0020328917920509),
    N2(0.12165961304,0.00204777893869357),
    N2(0.12371480209,0.00206258572541132),
    N2(0.12578475751,0.00207731157114911),
    N2(0.12786939806,0.00209195589802822),
    N2(0.12996864194,0.00210651813136895),
    N2(0.13208240677,0.00212099769971314),
    N2(0.13421060959,0.0021353940348466),
    N2(0.1363531669,0.00214970657182145),
    N2(0.13850999462,0.00216393474897821),
    N2(0.1406810081,0.00217807800796794),
    N2(0.14286612214,0.00219213579377407),
    N2(0.14506525101,0.00220610755473421),
    N2(0.14727830839,0.0022199927425618),
    N2(0.14950520745,0.00223379081236763),
    N2(0.1517458608,0.00224750122268123),
    N2(0.1540001805,0.00226112343547207),
    N2(0.15626807809,0.00227465691617074),
    N2(0.15854946458,0.00228810113368989),
    N2(0.16084425043,0.00230145556044507),
    N2(0.16315234559,0.00231471967237545),
    N2(0.1654736595,0.00232789294896439),
    N2(0.16780810104,0.00234097487325982),
    N2(0.17015557862,0.0023539649318946),
    N2(0.17251600011,0.0023668626151066),
    N2(0.1748892729,0.00237966741675873),
    N2(0.1772753038,0.00239237883435883),
    N2(0.1796739993,0.00240499636907933),
    N2(0.1820852651,0.00241751952577687),
    N2(0.1845090067,0.00242994781301172),
    N2(0.1869451289,0.00244228074306707),
    N2(0.1893935362,0.00245451783196814),
    N2(0.1918541325,0.00246665859950122),
    N2(0.1943268212,0.00247870256923247),
    N2(0.1968115052,0.00249064926852664),
    N2(0.1993080871,0.00250249822856562),
    N2(0.2018164689,0.00251424898436683),
    N2(0.2043365522,0.00252590107480147),
    N2(0.206868238,0.0025374540426126),
    N2(0.2094114271,0.0025489074344331),
    N2(0.2119660196,0.00256026080080349),
    N2(0.2145319152,0.00257151369618948),
    N2(0.2171090133,0.00258266567899957),
    N2(0.2196972128,0.00259371631160228),
    N2(0.222296412,0.00260466516034338),
    N2(0.224906509,0.00261551179556288),
    N2(0.2275274014,0.00262625579161192),
    N2(0.2301589863,0.00263689672686944),
    N2(0.2328011604,0.00264743418375874),
    N2(0.23545382,0.00265786774876389),
    N2(0.2381168611,0.0026681970124459),
    N2(0.2407901791,0.00267842156945886),
    N2(0.2434736692,0.00268854101856578),
    N2(0.246167226,0.00269855496265438),
    N2(0.2488707438,0.00270846300875265),
    N2(0.2515841166,0.00271826476804429),
    N2(0.2543072378,0.00272795985588395),
    N2(0.2570400006,0.00273754789181234),
    N2(0.2597822978,0.00274702849957115),
    N2(0.2625340217,0.0027564013071178),
    N2(0.2652950643,0.00276566594664009),
    N2(0.2680653174,0.00277482205457057),
    N2(0.2708446721,0.00278386927160087),
    N2(0.2736330195,0.00279280724269573),
    N2(0.2764302501,0.00280163561710702),
    N2(0.2792362541,0.00281035404838742),
    N2(0.2820509214,0.00281896219440405),
    N2(0.2848741416,0.00282745971735192),
    N2(0.2877058039,0.00283584628376715),
    N2(0.2905457971,0.00284412156454007),
    N2(0.2933940098,0.00285228523492813),
    N2(0.2962503302,0.00286033697456867),
    N2(0.2991146463,0.00286827646749144),
    N2(0.3019868457,0.00287610340213105),
    N2(0.3048668155,0.00288381747133917),
    N2(0.3077544429,0.00289141837239659),
    N2(0.3106496144,0.0028989058070251),
    N2(0.3135522166,0.0029062794813992),
    N2(0.3164621354,0.0029135391061576),
    N2(0.3193792567,0.00292068439641463),
    N2(0.322303466,0.00292771507177137),
    N2(0.3252346485,0.00293463085632669),
    N2(0.3281726893,0.00294143147868804),
    N2(0.331117473,0.00294811667198214),
    N2(0.3340688841,0.00295468617386541),
    N2(0.3370268067,0.00296113972653431),
    N2(0.3399911248,0.00296747707673542),
    N2(0.342961722,0.0029736979757754),
    N2(0.3459384819,0.00297980217953075),
    N2(0.3489212874,0.00298578944845736),
    N2(0.3519100217,0.00299165954759996),
    N2(0.3549045674,0.00299741224660128),
    N2(0.357904807,0.00300304731971117),
    N2(0.3609106227,0.00300856454579535),
    N2(0.3639218967,0.00301396370834421),
    N2(0.3669385107,0.00301924459548121),
    N2(0.3699603464,0.00302440699997124),
    N2(0.3729872852,0.00302945071922874),
    N2(0.3760192082,0.00303437555532566),
    N2(0.3790559966,0.00303918131499921),
    N2(0.3820975311,0.00304386780965947),
    N2(0.3851436924,0.00304843485539676),
    N2(0.3881943609,0.00305288227298887),
    N2(0.391249417,0.00305720988790811),
    N2(0.3943087407,0.00306141753032814),
    N2(0.397372212,0.00306550503513062),
    N2(0.4004397107,0.00306947224191174),
    N2(0.4035111163,0.00307331899498845),
    N2(0.4065863085,0.00307704514340463),
    N2(0.4096651664,0.00308065054093697),
    N2(0.4127475693,0.00308413504610072),
    N2(0.4158333961,0.00308749852215526),
    N2(0.4189225259,0.00309074083710945),
    N2(0.4220148374,0.00309386186372681),
    N2(0.4251102092,0.00309686147953051),
    N2(0.4282085198,0.00309973956680818),
    N2(0.4313096478,0.00310249601261655),
    N2(0.4344134713,0.00310513070878583),
    N2(0.4375198686,0.00310764355192403),
    N2(0.4406287177,0.00311003444342093),
    N2(0.4437398968,0.00311230328945204),
    N2(0.4468532836,0.00311445000098219),
    N2(0.449968756,0.00311647449376912),
    N2(0.4530861918,0.00311837668836669),
    N2(0.4562054686,0.00312015651012807),
    N2(0.459326464,0.00312181388920865),
    N2(0.4624490556,0.00312334876056875),
    N2(0.4655731207,0.00312476106397622),
    N2(0.4686985368,0.00312605074400877),
    N2(0.4718251813,0.00312721775005616),
    N2(0.4749529314,0.00312826203632217),
    N2(0.4780816644,0.00312918356182642),
    N2(0.4812112576,0.00312998229040596),
    N2(0.4843415881,0.0031306581907167),
    N2(0.487472533,0.00313121123623465),
    N2(0.4906039696,0.00313164140525691),
    N2(0.4937357749,0.0031319486809026),
    N2(0.496867826,0.00313213305111344),
    N1(0.5,0.0031321945086543)
  };

  schemes.push_back(gauss_scheme(3, data2));
  schemes.push_back(gauss_scheme(5, data3));
  schemes.push_back(gauss_scheme(7, data4));
  schemes.push_back(gauss_scheme(11, data6));
  schemes.push_back(gauss_scheme(15, data8));
  schemes.push_back(gauss_scheme(21, data11));
  schemes.push_back(gauss_scheme(31, data16));
  schemes.push_back(gauss_scheme(45, data23));
  schemes.push_back(gauss_scheme(63, data32));
  schemes.push_back(gauss_scheme(89, data45));
  schemes.push_back(gauss_scheme(125, data63));
  schemes.push_back(gauss_scheme(177, data89));
  schemes.push_back(gauss_scheme(251, data126));
  schemes.push_back(gauss_scheme(355, data178));
  schemes.push_back(gauss_scheme(501, data251));
  schemes.push_back(gauss_scheme(1001, data501));
}
