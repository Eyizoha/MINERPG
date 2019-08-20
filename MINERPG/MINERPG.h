#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>  
#include <fcntl.h>  
#include <process.h> 
#include <string>
#include <time.h>
#include <iostream>
#include <mmsystem.h>
#define PM SND_MEMORY|SND_ASYNC
#define BACKGROUNDCOLOR 0
#define GREEN 10
#define YELLOW 14
#define RED 12
#define BLUE 9
#define WHITE 15
#define CYAN 11
#define PURPLE 13
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define INC(x,n) (x)=(((x)+1)%(n))
#define DEC(x,n) (x)=(((x)+((n)-1))%(n))
#define AD 0
#define AP 1
#define RE 2
#define ATT 0
#define DEB 1
#define HPbar 0
#define MPbar 1
#define MVbar 2
#define ENEMYNUM 12 
using namespace std;
class role;
typedef struct buff{
	int duration;
	double ratio;	
}buff;
typedef struct status{
 	public:
 	bool who;//归属 
 	int classes;//职业 
	int HPmax,HP,HPrec;//最大生命，生命，生命回复 
	int MPmax,MP,MPrec;//最大法力，法力，法力回复 
	int atk,def;//攻击力，防御力 
	int abp,abr;//法术强度，法术抗性 
	int spd,avd;//速度，闪避 
	int crt,hit; //暴击，命中 
	double move;//行动条 
	buff attribute[8];//攻防强抗速闪暴命 
	buff debuff[4];//流血，燃烧，中毒，眩晕
	int skill;//技能书
	int lv;//等级 
	int cd[8];//冷却 
	int special;//特殊 
	bool rec;//复活 
}status;
typedef struct skillpara{
	string name;
	string explain;
	int spend;
	int cd;
	void (*sp)(status*);	
}skillpara;//技能参数 
typedef struct equip{
	int level;//等级
	int position;//位置：武器，头部，颈部，躯干，手部，足部 
	int rare;//品质：普通，优质，稀有，史诗，传说 
	int type;//20,11,02,匕，枪 	
	void newequip(int lv,int classes);
	void creat(int lv,int position,int rare,int type);
	bool showname(bool nom);
	void showexplain();
	void paraset(status* p);
	void effect(status* p);
}equip;//装备参数 
class role{
	private:
	int classes;//职业 
	int level;//等级 
	int exp;// 经验 or 给与经验 
	int vitality;//体力 
	int wit;//智力
	int strength;//力量  
	int spirit;//精神 
	int agility;//敏捷 
	int insight;//洞察 
	int skillnum;//技能书 
	equip equiplist[6];//装备 
	public:
	char name[9];//名字 
	int rank;//敌人序号 
	void creat();
	void creat(int r,int lv,int st,int vi,int wi,int sp,int ag,int in);
	void createnemy(int rank);
	bool save();
	bool load(string);
	void display(int,bool re=true);
	int returnlv();
	int returnexp();
	equip returnequ(int);
	bool victory();
	bool defeat();
	void getexp(int);
	void levelup();
	void resetpoint();
	void explainequip();
	bool changeequ(equip);
	void showequip(); 
	status battlestatus(bool);
	//
	void (*sskp)();
	void (*opp)(status*);
};
void setbgm(int);
void gotoxy(int x, int y);
void color(int c);
void color(int c,int b);
bool space_esc();
void initialize();
int menu(); 
void start(int);
bool illustration(bool);
void drawmenu();
void drawboard();
bool hitthat(double);
int choose(int n,string* p);
int choose(int n,string* p,string* explain,int k=0);
int skillchoose(status* p,int n,string* name,string* explain);
void drawbar(double);
void drawmvbar(double,bool);
void writenum(int,int);
bool battle();
void showskill();
void showmessage(string);
status* whoseturn(status*,status*);
status* turnstart(status*);
void turnend(status*);
bool operate(status*);
void setbuff(status*,int,int,int,double);
void dealbuff(status*);
int damage(status*,int,double,int);//谁，类，多少，目标 
void showbar(status);
void showsta(status);
void showbuff(status);
string percent(double);
//技能：战士 
void w_bloodsuck(status*);
void w_beatback(status*,double);
void w_0attack(status*);
void w_1charge(status*);
void w_2disarm(status*);
void w_3stone(status*);
void w_4cripple(status*);
void w_5shieldhit(status*);
void w_6bloodwake(status*);
void w_7rage(status*);
//技能：法师
void m_manasuck(status*);
void m_phaseblink(status*);
void m_0attack(status*);
void m_1enchants(status*);
void m_2stormshieldl(status*);
void m_3snowstorm(status*);
void m_4icelance(status*);
void m_5mindblast(status*);
void m_6muse(status*);
void m_7manaburn(status*); 
//技能：刺客
void a_doubledagger(status*);
void a_preparation(status*);
void a_0attack(status*); 
void a_1assassinate(status*);
void a_2blindingpowder(status*);
void a_3sneak(status*);
void a_4poisondagger(status*);
void a_5stickstrike(status*);
void a_6weakagent(status*);
void a_7fatalrhythm(status*);
//技能：咒术师
void c_vicious(status*);
void c_boundary(status*);
void c_0attack(status*); 
void c_1sectumsempra(status*);
void c_2blaze(status*);
void c_3fivepoisons(status*);
void c_4daemon(status*);
void c_5increase(status*);
void c_6imperio(status*);
void c_7summarycurse(status*);
//技能：神枪手
void s_showbullet(status*);
void s_burstbullet(status*);
void s_momentumshoot(status*);
void s_0attack(status*); 
void s_1quickfire(status*);
void s_2deadeyeshoot(status*);
void s_3tacticalcounter(status*);
void s_4interceptingshoot(status*);
void s_5quickreload(status*);
void s_6deathmarker(status*);
void s_7stormshoot(status*);
//技能：影武士
void d_shadowchop(status*);
void d_shadowstep(status*);
void d_0attack(status*);
void d_1shadowblade(status*);
void d_2curseshadow(status*);
void d_3triplechop(status*);
void d_4intoshadow(status*);
void d_5shadowdurance(status*);
void d_6bloodsacrifice(status*);
void d_7shadowswordcircle(status*);
//
void e_regenerate(status*);
void e_gaze(status*);
//敌人设定 
void e_showsk(){return;}
void e1_op(status*);
void e1_attack(status*);
void e3_op(status*);
void e3_attack(status*);
void e3_sk(status*);
void e3_showsk();
void e4_showsk();
void e4_op(status*);
void e4_attack(status*);
void e5_showsk();
void e5_op(status*);
void e5_attack(status*);
void e6_showsk();
void e6_op(status*);
void e7_op(status*);
void e8_showsk();
void e8_op(status*);
void e8_attack(status*);
void e9_showsk();
void e9_op(status*);
void e10_showsk();
void e10_op(status*);
void e10_sk(status*,double);
void e10_attack(status*);
void e11_showsk();
void e11_op(status*);
void e11_sk(status*,double);
void e11_attack(status*);
void e12_showsk();
void e12_op(status*);
void e12_sk(status*,double);
void e12_attack(status*); 
//
