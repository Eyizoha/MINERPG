#include "MINERPG.h"
extern char men[];
extern char bat[];
extern char bat2[];
extern char bat3[];
extern char wta[];
extern char sta[];
extern char win[];
extern char los[];
extern char upp[];
extern char dow[];
extern char cho[];
extern char r_0[];
extern char r_1[];
extern char r_2[];
extern char r_3[];
extern char r_4[];
extern char r_5[];
extern char a_0[];
extern char a_1[];
extern char a_2[];
extern char a_3[];
extern char a_4[];
extern char a_5[];
extern char a_6[];
extern char m_0[];
extern char m_1[];
extern char m_2[];
extern char m_3[];
extern char m_4[];
extern char m_5[];
extern char m_6[];
extern char m_7[];
extern char w_0[];
extern char w_1[];
extern char w_2[];
extern char w_3[];
extern char w_4[];
extern char w_5[];
extern char w_6[];
extern char w_7[];
extern char c_0[];
extern char c_1[];
extern char c_2[];
extern char c_3[];
extern char c_4[];
extern char c_5[];
extern char c_6[];
extern char c_7[];
extern char s_0[];
extern char s_1[];
extern char s_2[];
extern char s_3[];
extern char s_6[];
extern char d_0[];
extern char d_1[];
extern char d_2[];
extern char d_3[];
extern char d_4[];
extern char d_5[];
extern char d_6[];
extern char d_7[];
//
int hpipe[2];
bool pvp,esc;
role myrole,enemyrole;
status player,enemy;
int mgeline,row;
double lastmvp,lastmve;
skillpara sl[6][8];
int bulletspend[8];
int magicnum[7] = {0x45,0x79,0x69,0x7A,0x6F,0x68,0x61};
string classesname[6]= {"战士","法师","刺客","咒术师","神枪手","影武士"};
//
const int rarecolor[6]= {WHITE,GREEN,CYAN,PURPLE,YELLOW,RED};
const string rarelist[6]= {"普通","精良","稀有","史诗","传说","神器"};
const string metal[5]= {"铁制","钢制","秘银","星陨","战争之影"};
const string nonmetal[5]= {"木制","骨制","石英","钢玉","远古之心"};
const string cloth[5]= {"布制","皮制","凤羽","逆鳞","风暴之息"};
const string gem[5]= {"青金","水晶","钻石","黑耀","恒星之眼"};
//
const string positionlist[6]= {"武器","头部","颈部","躯干","手部","足部"};
const string weapon[6]= {"长剑","法杖","匕首","咒刃","左轮","太刀"};
const string head[3]= {"头盔","兜帽","目镜"};
const string neck[3]= {"护符","项链","吊坠"};
const string trunk[3]= {"铠甲","斗篷","法袍"};
const string hand[3]= {"手套","手镯","戒指"};
const string foot[3]= {"长靴","战靴","短靴"};
//
void equip::newequip(int lv,int classes)
{
    level=lv;
    position=rand()%6;
    int r;
    r=rand()%100;
    if(lv>30&&r<1){PlaySound(r_5,NULL,PM);rare=5;}
    else if(r<5){PlaySound(r_4,NULL,PM);rare=4;}
    else if(r<10){PlaySound(r_3,NULL,PM);rare=3;}
    else if(r<15){PlaySound(r_2,NULL,PM);rare=2;}
    else if(r<20){PlaySound(r_1,NULL,PM);rare=1;}
    else {PlaySound(r_0,NULL,PM);rare=0;}
    if(position)type=rand()%3;
    else type=classes;
    if(rare==5)
    {
        level=myrole.returnlv();
        if(position)type=1;
    }
}
void equip::creat(int lv,int ra,int pos,int ty)
{
    level=lv;
    rare=ra;
    position=pos;
    type=ty;
}
bool equip::showname(bool nom)
{
    if(!level)return false;
    string name;
    if(rare==5)
    {
        switch(position)
        {
        case 0:
            name="死神的噬魂"+weapon[type];
            break;
        case 1:
            name="死神的诅咒假面";
            break;
        case 2:
            name="死神的永生之石";
            break;
        case 3:
            name="死神的暗影披风";
            break;
        case 4:
            name="死神的轮回指环";
            break;
        case 5:
            name="死神的虚空之靴";
            break;
        }
        if(nom)color(rarecolor[rare]);
        else color(BACKGROUNDCOLOR,rarecolor[rare]);
        cout<<name;
        return true;
    }
    switch(position)
    {
    case 0://武器
    {
        if(type==0||type==2||type==4)
            name=metal[rare]+weapon[type];
        else
            name=nonmetal[rare]+weapon[type];
    }
    break;
    case 1://头
    {
        if(type==0||type==2)
            name=metal[rare]+head[type];
        else
            name=cloth[rare]+head[type];
    }
    break;
    case 2://颈
    {
        if(type==0)
            name=nonmetal[rare]+neck[type];
        else
            name=gem[rare]+neck[type];
    }
    break;
    case 3://躯
    {
        if(type==0)
            name=metal[rare]+trunk[type];
        else
            name=cloth[rare]+trunk[type];
    }
    break;
    case 4://手
    {
        if(type==0)
            name=cloth[rare]+hand[type];
        else if(type==1)
            name=nonmetal[rare]+hand[type];
        else
            name=gem[rare]+hand[type];
    }
    break;
    case 5://足
    {
        if(type==0||type==2)
            name=cloth[rare]+foot[type];
        else
            name=metal[rare]+foot[type];
    }
    break;
    }
    if(nom)color(rarecolor[rare]);
    else color(BACKGROUNDCOLOR,rarecolor[rare]);
    cout<<name;
    return true;
}
void equip::showexplain()
{
    if(!level)return;
    double basenum;
    basenum=0.2*(rare==5?5:rare+1)*level;
    int a,b,n;
    n=(int)basenum;
    if(!n)n=1;
    b=n/2;
    a=n-b;
    if(rare!=5)
    {
        color(WHITE);
        cout<<"等级:"<<level;
    }
    else
    {
        color(WHITE);
        cout<<"等级:";
        color(RED);
        cout<<level;
    }
    color(WHITE);
    cout<<"┃品质:";
    color(rarecolor[rare]);
    cout<<rarelist[rare];
    color(WHITE);
    cout<<"┃位置:";
    switch(position)
    {
    case 0:
    {
        cout<<"武器┃属性:";
        if(type==0)
        {
            cout<<"攻击+";
            cout<<n*3;
        }
        else if(type==1)
        {
            cout<<"法强+";
            cout<<n*3;
        }
        else if(type==2)
        {
            cout<<"攻击+";
            cout<<a*3;
            cout<<"，";
            cout<<"暴击+";
            cout<<b*3;
        }
        else if(type==3)
        {
            cout<<"攻击+";
            cout<<a*3;
            cout<<"，";
            cout<<"法强+";
            cout<<b*3;
        }
        else if(type==4)
        {
            cout<<"攻击+";
            cout<<a*3;
            cout<<"，";
            cout<<"命中+";
            cout<<b*4;
        }
        else if(type==5)
        {
            cout<<"攻击+";
            cout<<a*3;
            cout<<"，";
            cout<<"速度+";
            cout<<b*3;
        }
    }
    break;
    case 1://头
    {
        cout<<"头部┃属性:";
        if(type==0)
        {
            cout<<"暴击+";
            cout<<n*3;
        }
        else if(type==1)
        {
            cout<<"暴击+";
            cout<<a*3;
            cout<<"，";
            cout<<"命中+";
            cout<<b*4;
        }
        else if(type==2)
        {
            cout<<"命中+";
            cout<<n*4;
        }
    }
    break;
    case 2://颈
    {
        cout<<"颈部┃属性:";
        if(type==0)
        {
            cout<<"生命+";
            cout<<n*20;
        }
        else if(type==1)
        {
            cout<<"生命+";
            cout<<a*20;
            cout<<"，";
            cout<<"法力+";
            cout<<b*20;
        }
        else if(type==2)
        {
            cout<<"法力+";
            cout<<n*20;
        }
    }
    break;
    case 3://躯
    {
        cout<<"躯干┃属性:";
        if(type==0)
        {
            cout<<"护甲+";
            cout<<n*2;
        }
        else if(type==1)
        {
            cout<<"护甲+";
            cout<<a*2;
            cout<<"，";
            cout<<"魔抗+";
            cout<<b*2;
        }
        else if(type==2)
        {
            cout<<"魔抗+";
            cout<<n*2;
        }
    }
    break;
    case 4://手
    {
        cout<<"手部┃属性:";
        if(type==0)
        {
            cout<<"生命恢复+";
            cout<<n*1;
        }
        else if(type==1)
        {
            cout<<"生命恢复+";
            cout<<a*1;
            cout<<"，";
            cout<<"法力恢复+";
            cout<<b*1;
        }
        else if(type==2)
        {
            cout<<"法力恢复+";
            cout<<n*1;
        }
    }
    break;
    case 5://足
    {
        cout<<"足部┃属性:";
        if(type==0)
        {
            cout<<"速度+";
            cout<<n*3;
        }
        else if(type==1)
        {
            cout<<"速度+";
            cout<<a*3;
            cout<<"，";
            cout<<"闪避+";
            cout<<b*4;
        }
        else if(type==2)
        {
            cout<<"闪避+";
            cout<<n*3;
        }
    }
    break;
    }
    if(rare==5)
    {
        cout<<"┃效果:";
        switch(position)
        {
        case 0:
            cout<<"回合开始时，若未眩晕则对敌方造成基于等级的真实伤害";
            break;
        case 1:
            cout<<"战斗开始时，对敌方施加3回合伤害基于等级的所有症状";
            break;
        case 2:
            cout<<"每场战斗限一次，阵亡时以50%的生命和法力复活";
            break;
        case 3:
            cout<<"回合结束时，所有减益效果持续回合-1";
            break;
        case 4:
            cout<<"回合结束时，所有技能剩余冷却回合-1";
            break;
        case 5:
            cout<<"回合结束时，增加20%的行动条";
            break;
        }
    }
    cout<<"。";
}
void equip::paraset(status* p)
{
    if(!level)return;
    double basenum;
    basenum=0.2*(rare==5?5:rare+1)*level;
    int a,b,n;
    n=(int)basenum;
    if(!n)n=1;
    b=n/2;
    a=n-b;
    switch(position)
    {
    case 0://武器
    {
        if(type==0)p->atk+=n*3;
        else if(type==1)p->abp+=n*3;
        else if(type==2)p->atk+=a*3,p->crt+=b*3;
        else if(type==3)p->atk+=a*3,p->abp+=b*3;
        else if(type==4)p->atk+=a*3,p->hit+=b*4;
        else if(type==5)p->atk+=a*3,p->spd+=b*3;
    }
    break;
    case 1://头
    {
        if(type==0)p->crt+=n*3;
        else if(type==1)p->crt+=a*3,p->hit+=b*4;
        else if(type==2)p->hit+=n*4;
    }
    break;
    case 2://颈
    {
        if(type==0)p->HPmax+=n*20;
        else if(type==1)p->HPmax+=a*20,p->MPmax+=b*20;
        else if(type==2)p->MPmax+=n*20;
    }
    break;
    case 3://躯
    {
        if(type==0)p->def+=n*2;
        else if(type==1)p->def+=a*2,p->abr+=b*2;
        else if(type==2)p->abr+=n*2;
    }
    break;
    case 4://手
    {
        if(type==0)p->HPrec+=n*1;
        else if(type==1)p->HPrec+=a*1,p->MPrec+=b*1;
        else if(type==2)p->MPrec+=n*1;
    }
    break;
    case 5://足
    {
        if(type==0)p->spd+=n*3;
        else if(type==1)p->spd+=a*3,p->avd+=b*4;
        else if(type==2)p->avd+=n*4;
    }
    break;
    }
}
void equip::effect(status* p)
{
    if(!level)return;
    if(rare!=5)return;
    switch(position)
    {
    case 0://武器
    {
        string s;
        status *e;
        if(p->who)
        {
            s=myrole.name;
            e=&enemy;
        }
        else
        {
            s=enemyrole.name;
            e=&player;
        }
        color(WHITE);
        showmessage(s+"触发被动死神的噬魂，造成真实伤害。");
        damage(e,RE,-p->lv,HPbar);
    }
    break;
    case 1://头
    {
        string s;
        status *e;
        if(p->who)
        {
            s=myrole.name;
            e=&enemy;
        }
        else
        {
            s=enemyrole.name;
            e=&player;
        }
        color(WHITE);
        showmessage(s+"触发被动死神的诅咒，施加流血、燃烧和中毒。");
        for(int i=0; i<3; i++)
        {
            e->debuff[i].duration=3;
            e->debuff[i].ratio=p->lv;
        }
        dealbuff(e);
    }
    break;
    case 2://颈
    {
        if(p->rec)
        {
            string s;
            if(p->who)s=myrole.name;
            else s=enemyrole.name;
            color(WHITE);
            showmessage(s+"触发被动死神的永生，复活。");
            p->HP=p->HPmax/2;
            p->MP=p->MPmax/2;
            showbar(*p);
            p->rec=false;
        }
        else return;
    }
    break;
    case 3://躯
    {
        string s;
        bool hit=false;
        if(p->who)s=myrole.name;
        else s=enemyrole.name;
        for(int i=0; i<8; i++)
            if(p->attribute[i].ratio<0)
                if(p->attribute[i].duration)
                {
                    hit=true;
                    p->attribute[i].duration--;
                }
        for(int i=0; i<4; i++)
            if(p->debuff[i].duration)
            {
                hit=true;
                p->debuff[i].duration--;
            }
        if(hit)
        {
            color(WHITE);
            showmessage(s+"触发被动死神的暗影，减益效果持续回合-1。");
        }
        dealbuff(p);
    }
    break;
    case 4://手
    {
        string s;
        bool hit=false;
        if(p->who)s=myrole.name;
        else s=enemyrole.name;
        for(int i=0; i<8; i++)if(p->cd[i])
            {
                hit=true;
                p->cd[i]--;
            }
        if(hit)
        {
            color(WHITE);
            showmessage(s+"触发被动死神的轮回，技能剩余冷却回合-1。");
        }
        dealbuff(p);
    }
    break;
    case 5://足
    {
        string s;
        if(p->who)s=myrole.name;
        else s=enemyrole.name;
        color(WHITE);
        showmessage(s+"触发被动死神的虚空，增加行动条。");
        damage(p,RE,0.20,MVbar);
    }
    break;
    }
}
//
void role::creat()
{
    level=1;
    exp=0;
    skillnum=2;
    cout<<"输入新角色名字(回车结束,最大10个字符,汉字占2字符,会覆盖同名角色!!!): ";
    cin>>name;
    cout<<"选择职业: ";
    string explain[6];
    explain[0]="战士是一种古老而强大的职业，天生拥有较高的力量和体力。"
               "顽强的生存能力能使战士正面迎接敌人的攻击，"
               "而强大的力量能让战士给予敌人迎头痛击。"
               "战士擅长破坏敌人的武器、摧毁敌人的护甲和使敌人流血"
               "从而无法自然恢复生命。";
    explain[1]="法师是一种神秘而多变的职业，天生拥有较高的智力和精神。"
               "法师多变的控制法术能从各种方面限制敌人的能力，"
               "而强大的攻击魔法能给敌人带来毁灭。"
               "法师擅长削弱敌人的精神、用各种法术限制敌人和使敌人"
               "燃烧从而无法自然恢复法力。";
    explain[2]="刺客是一种灵活而致命的职业，天生拥有较高的敏捷和洞察。"
               "刺客灵活的身手可以使其规避敌人的攻击并快速行动，"
               "而极高的爆发能力可以让刺客瞬间对敌人造成致命伤害。"
               "刺客擅长限制敌人的攻击能力、快速致命地攻击敌人和使用毒药"
               "对敌人造成无法抵挡的伤害。";
    explain[3]="咒术师是一种恶毒而恐怖的职业，天生拥有较为全面的属性。"
               "咒术师可以使用各种让敌人陷入持续伤害的咒术，"
               "同时还拥有可以让持续伤害瞬间爆发的强大能力。"
               "咒术师擅长限制敌人的回复能力并对其造成持续的伤害，全面的"
               "伤害能力可以应付各种敌人。";
    explain[4]="神枪手是一种极致而华丽的职业，天生拥有较高的洞察。"
               "神枪手掌握了各种射击技巧，可以通过连招瞬间爆发大量伤害，"
               "同时其强大的行动条控制能力可以极大地限制敌人行动。"
               "神枪手擅长通过技能连招来攻击敌人，超高的爆发能力"
               "往往可以在敌人反击之前将其击败。";
    explain[5]="影武士是一种危险而疯狂的职业，天生拥有较高的力量和精神。"
               "影武士附加了魔法的斩击能造成物理和精神上的双重伤害，"
               "通过独特的暗影魔法能极大地强化自身或限制敌人的施法。"
               "影武士擅长通过附有暗影之力的斩击蚕食敌人的体力与精神，"
               "还拥有绝境下背水一战的能力。";
    classes=choose(6,classesname,explain);
    switch(classes)
    {
    case 0://战士
        strength=vitality=8;
        wit=spirit=5;
        agility=insight=5;
        break;
    case 1://法师
        strength=vitality=5;
        wit=spirit=8;
        agility=insight=5;
        break;
    case 2://刺客
        strength=vitality=5;
        wit=spirit=5;
        agility=insight=8;
        break;
    case 3://咒术师
        strength=vitality=6;
        wit=spirit=6;
        agility=insight=6;
        break;
    case 4://神枪手
        strength=vitality=5;
        wit=spirit=5;
        agility=6;
        insight=10;
        break;
    case 5://影武士 
        vitality=wit=5;
        strength=spirit=8;
        agility=insight=5;
        break;
    }
    rank=0;
    memset(equiplist,0,sizeof(equiplist));
    if(!strcmp(name,"Eyizoha"))
    {
        equiplist[0].creat(1,5,0,classes);
        for(int i=1; i<6; i++)equiplist[i].creat(1,5,i,1);
    }
}
void role::creat(int r,int ra,int vi,int wi,int st,int sp,int ag,int in)
{
    classes=-1;
    level=ra+1;
    exp=2*level-1;
    strength=r*st;
    vitality=r*vi;
    wit=r*wi;
    spirit=r*sp;
    agility=r*ag;
    insight=r*in;
    memset(equiplist,0,sizeof(equiplist));
}
void role::createnemy(int rank)
{
	int r,n;
	n=rank%ENEMYNUM+1;r=rank/ENEMYNUM+1;
	//00|01,10|12,20|22,30|32,40|42,50|52 
	//攻|强,暴|命,生|法,护|抗,治|复,速|闪 
	switch(n)
	{
		case 1:
			this->creat(r,rank,5,0,4,4,4,4);
	    	strcpy(this->name,"骷髅");
	   		this->sskp=e_showsk;
			this->opp=e1_op;
   		break;
   		case 2:
			this->creat(r,rank,6,0,5,5,5,5);
	    	strcpy(this->name,"强化骷髅");
	   		this->sskp=e_showsk;
			this->opp=e1_op;
   		break;
   		case 3:
			this->creat(r,rank,7,0,6,6,6,6);
	    	strcpy(this->name,"诅咒骷髅");
	   		this->sskp=e3_showsk;
			this->opp=e1_op;
   		break;
   		case 4:
			this->creat(r,rank,9,2,8,5,5,5);
	    	strcpy(this->name,"骷髅勇士");
	   		this->sskp=e4_showsk;
			this->opp=e4_op;
   		break;
   		case 5:
			this->creat(r,rank,7,8,2,8,5,6);
	    	strcpy(this->name,"灰烬尸巫");
	   		this->sskp=e5_showsk;
			this->opp=e5_op;
			this->equiplist[3].creat(4*r,4,3,0);
   		break;
   		case 6:
			this->creat(r,rank,7,0,8,6,10,6);
	    	strcpy(this->name,"诅咒幽灵");
	   		this->sskp=e3_showsk;
			this->opp=e6_op;
   		break;
   		case 7:
			this->creat(r,rank,7,4,4,8,6,6);
	    	strcpy(this->name,"摄魂尸巫");
	   		this->sskp=e_showsk;
			this->opp=e7_op;
			this->equiplist[3].creat(4*r,4,3,0);
   		break;
   		case 8:
			this->creat(r,rank,9,4,8,4,2,6);
	    	strcpy(this->name,"死亡骑士");
	   		this->sskp=e8_showsk;
			this->opp=e8_op;
			this->equiplist[5].creat(6*r,4,5,0);
   		break;
   		case 9:
			this->creat(r,rank,7,6,6,4,10,10);
	    	strcpy(this->name,"致命阴影");
	   		this->sskp=e9_showsk;
			this->opp=e9_op;
			this->equiplist[0].creat(10*r,4,0,0);
   		break;
   		case 10:
			this->creat(r,rank,8,8,8,8,8,8);
	    	strcpy(this->name,"吸血鬼王");
	   		this->sskp=e10_showsk;
			this->opp=e10_op;
   		break;
   		case 11:
			this->creat(r,rank,12,6,4,4,6,6);
	    	strcpy(this->name,"守卫石像");
	   		this->sskp=e11_showsk;
			this->opp=e11_op;
			this->equiplist[3].creat(16*r,4,3,1);
   		break;
   		case 12:
			this->creat(r,rank,10,2,6,6,10,10);
	    	strcpy(this->name,"蛇发女妖");
	   		this->sskp=e12_showsk;
			this->opp=e12_op;
			this->equiplist[3].creat(18*r,4,2,2);
   		break;
	}
}
bool role::save()
{
    FILE *fp;
    role p;
    do
    {
        fp=fopen(name,"wb");
        if(fp==NULL)return false;
        fwrite(this,sizeof(role),1,fp);
        fclose(fp);
        fp=fopen(name,"rb");
        fread(&p,sizeof(role),1,fp);
        fclose(fp);
    }
    while(memcmp(&p,this,sizeof(role)));
    return true;
}
bool role::load(string str)
{
    FILE *fp;
    fp=fopen(str.c_str(),"rb");
    if(fp==NULL)return false;
    fread(this,sizeof(role),1,fp);
    fclose(fp);
    return true;
}
int role::returnlv()
{
    return level;
}
int role::returnexp()
{
    return exp;
}
equip role::returnequ(int i)
{
    return equiplist[i];
}
void role::display(int y,bool re)
{
    if(re)
    {
        color(WHITE);
        gotoxy(0,y+0);
        cout<<"┏角色信息━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
        gotoxy(0,y+1);
        cout<<"┃名字:                 ┃体力:          智力:          力量:          精神:          敏捷:          洞察:              ┃";
        gotoxy(0,y+2);
        cout<<"┃职业:                 ┃装备:                                                                                         ┃";
        gotoxy(0,y+3);
        cout<<"┃等级:                 ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫";
        gotoxy(0,y+4);
        cout<<"┃经验:                 ┃被动技能:                                                                                     ┃";
        gotoxy(0,y+5);
        cout<<"┃通关等级:             ┃主动技能:                                                                                     ┃";
        gotoxy(0,y+6);
        cout<<"┗━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
        //
        gotoxy(7,y+1);
        cout<<name;
        //
        gotoxy(7,y+2);
        cout<<classesname[classes];
        //装备
        gotoxy(31,y+2);
        for(int i=0; i<6; i++)if(equiplist[i].showname(true)&&i!=5)cout<<" ";
        //
        color(WHITE);
        gotoxy(7,y+3);
        cout<<level;
        //
        gotoxy(7,y+4);
        cout<<exp<<"/"<<level*level;
        gotoxy(35,y+4);
        switch(classes)
        {
        case 0://战士
            cout<<"不屈意志 ";
            if(level>=4)cout<<"嗜血 ";
            if(level>=10)cout<<"猛击 ";
            break;
        case 1://法师
            cout<<"智慧棱镜 ";
            if(level>=4)cout<<"嗜法 ";
            if(level>=10)cout<<"相位转移 ";
            break;
        case 2://刺客
            cout<<"刺客本能 ";
            if(level>=4)cout<<"双匕 ";
            if(level>=10)cout<<"伺机待发 ";
            break;
        case 3://咒术师
            cout<<"咒刃契约 ";
            if(level>=4)cout<<"恶毒 ";
            if(level>=10)cout<<"宁静结界 ";
            break;
        case 4://神枪手
            cout<<"射手专注 ";
            if(level>=4)cout<<"爆裂子弹 ";
            if(level>=10)cout<<"动量射击 ";
            break;
        case 5://影武士 
            cout<<"影裔血统 ";
            if(level>=4)cout<<"斩影 ";
            if(level>=10)cout<<"暗影步 ";
            break;
        }
        //
        gotoxy(11,y+5);
        cout<<rank;
        gotoxy(35,y+5);
        for(int i=0; i<skillnum; i++)cout<<sl[classes][i].name<<" ";
    }
    gotoxy(31,y+1);
    cout<<vitality;
    gotoxy(46,y+1);
    cout<<wit;
    gotoxy(61,y+1);
    cout<<strength;
    gotoxy(76,y+1);
    cout<<spirit;
    gotoxy(91,y+1);
    cout<<agility;
    gotoxy(106,y+1);
    cout<<insight;
    gotoxy(0,y+7);
}
bool role::victory()
{
    rank++;
    system("cls");
    display(0);
    PlaySound(win,NULL,PM);
    color(GREEN);
    cout<<"战斗胜利！\n";
    color(WHITE);
    getexp(enemyrole.returnexp());
    space_esc();
    //
    if(hitthat(0.6))
    {
        system("cls");
        display(0);
        color(GREEN);
        cout<<"获得新装备！\n";
        color(WHITE);
        equip equ;
        equ.newequip(enemyrole.returnlv(),classes);
        equ.showname(true);
        cout<<"\n";
        equ.showexplain();
        cout<<"\n";
        if(!changeequ(equ))return false;
    }
    //
    while(1)
    {
        system("cls");
        display(0);
        gotoxy(0,39);
        if(save())cout<<"进度保存成功！";
        else cout<<"进度保存失败！";
        gotoxy(0,40);
        cout<<"选择操作:";
        string list[4]= {"继续挑战","查看装备","重置属性点","返回菜单"};
        switch(choose(4,list))
        {
        case 0:
            return true;
        case 1:
            explainequip();
            break;
        case 2:
            resetpoint();
            break;
        case 3:
            return false;
        default:
            return false;
        }
    }
}
bool role::defeat()
{
    PlaySound(los,NULL,PM);
    system("cls");
    display(0);
    color(RED);
    cout<<"战斗失败！\n";
	color(WHITE);
    cout<<"失去"<<enemyrole.returnlv()<<"点经验。\n";
    exp-=enemyrole.returnlv();if(exp<0)exp=0; 
    space_esc();
    while(1)
    {
        system("cls");
        display(0);
        gotoxy(0,39);
        if(save())cout<<"进度保存成功！";
        else cout<<"进度保存失败！";
        gotoxy(0,40);
        cout<<"选择操作:";
        string list[5]= {"重新挑战","挑战上一关","查看装备","重置属性点","返回菜单"};
        switch(choose(5,list))
        {
        case 0:
            return true;
        case 1:
            if(rank)rank--;
            return true;
        case 2:
            explainequip();
            break;
        case 3:
            resetpoint();
            break;
        case 4:
            return false;
        default:
            return false;
        }
    }
}
void role::getexp(int ex)
{
    cout<<"获得"<<ex<<"点经验。\n";
    exp+=ex;
    cout<<"经验/下级经验:"<<exp<<"/"<<level*level;
    while(exp>=(level*level))levelup();
}
void role::resetpoint()
{
    system("cls");
    int point=level;
    if(point==1)
    {
        display(0);
        return;
    }
    switch(classes)
    {
    case 0://战士
        strength=vitality=8;
        wit=spirit=5;
        agility=insight=5;
        break;
    case 1://法师
        strength=vitality=5;
        wit=spirit=8;
        agility=insight=5;
        break;
    case 2://刺客
        strength=vitality=5;
        wit=spirit=5;
        agility=insight=8;
        break;
    case 3://咒术师
        strength=vitality=6;
        wit=spirit=6;
        agility=insight=6;
        break;
    case 4://神枪手
        strength=vitality=5;
        wit=spirit=5;
        agility=6;
        insight=10;
        break;
    case 5://影武士 
        vitality=wit=5;
        strength=spirit=8;
        agility=insight=5;
        break;
    }
    display(0);
    color(WHITE);
    switch(classes)
    {
    case 0://战士
        cout<<"不屈意志:每点体力额外提高10点生命和2点魔抗。";
        break;
    case 1://法师
        cout<<"智慧棱镜:每点智力额外提高1点法强和4点命中。";
        break;
    case 2://刺客
        cout<<"刺客本能:每点敏捷额外提高1点攻击和1点速度，每点洞察额外提高2点闪避。";
        break;
    case 3://咒术师
        cout<<"咒刃契约:每点力量额外提高2点法强，每点精神额外提高2点攻击。";
        break;
    case 4://神枪手
        cout<<"射手专注:每点洞察额外提高1点攻击、1点速度和1点命中。";
        break;
    case 5://影武士 
        cout<<"影裔血统:每点力量额外提高10点生命，每点精神额外提高10点法力。";
        break;
    }
    CONSOLE_SCREEN_BUFFER_INFO xy;
    int k=0;
    cout<<"\n选择属性提升(";
    string list[6]= {"体力","智力","力量","精神","敏捷","洞察"};
    string explain[6];
    explain[0]="每点体力可以提高20点最大生命值和1点生命恢复。";
    explain[1]="每点智力可以提高20点最大法力值和1点法力恢复。";
    explain[2]="每点力量可以提高3点攻击和2点护甲。";
    explain[3]="每点精神可以提高3点法强和2点魔抗。";
    explain[4]="每点敏捷可以提高3点速度和4点闪避。";
    explain[5]="每点洞察可以提高3点暴击和4点命中。";
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    while(--point)
    {
        cout<<point<<"):";
        switch(k=choose(6,list,explain,k))
        {
        case 0://体力
            vitality++;
            break;
        case 1://智力
            wit++;
            break;
        case 2://力量
            strength++;
            break;
        case 3://精神
            spirit++;
            break;
        case 4://敏捷
            agility++;
            break;
        case 5://洞察
            insight++;
            break;
        }
        display(0,false);
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
    }
    gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
    cout<<point<<"):";
}
void role::explainequip()
{
    system("cls");
    display(0);
    int t=0,i=0,n=0;
    for(i=0; i<6; i++)if(equiplist[i].level)n++;
    if(!n)return;
    char ch=0;
    bool ar;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    cout<<"空格键丢弃装备，ESC键返回。\n";
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    while(!equiplist[t].level)INC(t,6);
    while(1)
    {
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
        for(i=0; i<6; i++)
        {
            ar=false;
            if(i==t)ar=equiplist[i].showname(false);
            else ar=equiplist[i].showname(true);
            color(WHITE);
            if(ar)cout<<" ";
        }
        gotoxy(0,xy.dwCursorPosition.Y+1);
        cout<<"                                                                                                                          ";
        gotoxy(0,xy.dwCursorPosition.Y+1);
        equiplist[t].showexplain();
        ch=getch();
        if(ch==0)ch=getch();
        if(ch==LEFT)do
            {
                DEC(t,6);
            }
            while(!equiplist[t].level);
        if(ch==RIGHT)do
            {
                INC(t,6);
            }
            while(!equiplist[t].level);
        if(ch==' ')
        {
            gotoxy(0,xy.dwCursorPosition.Y+2);
            color(RED);
            cout<<"确定丢弃？";
            string list[2]= {"否","是"};
            switch(choose(2,list))
            {
            case 0:
                break;
            case 1:
                equiplist[t].level=0;
                equiplist[t].rare=0;
                n--;
                if(!n)return;
                do
                {
                    INC(t,6);
                }
                while(!equiplist[t].level);
                gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
                cout<<"                                                                                                                          ";
                break;
            default:
                return;
            }
            gotoxy(0,xy.dwCursorPosition.Y+2);
            cout<<"               ";
            display(0);
        }
        if(ch==0x1B)return;
    }
}
void role::levelup()
{
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    color(YELLOW);
    level++;
    //
    for(int i=0; i<6; i++)if(equiplist[i].rare==5)equiplist[i].level=level;
    //
    if((level%2==0)&&(1<=(level/2))&&((level/2)<=8))
    {
        if(level!=4&&level!=10)skillnum++;
        cout<<"\n等级提升!习得新技能!\n";
    }
    else cout<<"\n等级提升!           \n";
    //
    color(WHITE);
    switch(classes)
    {
    case 0://战士
        cout<<"不屈意志:每点体力额外提高10点生命和2点魔抗。";
        break;
    case 1://法师
        cout<<"智慧棱镜:每点智力额外提高1点法强和4点命中。";
        break;
    case 2://刺客
        cout<<"刺客本能:每点敏捷额外提高1点攻击和1点速度，每点洞察额外提高2点闪避。";
        break;
    case 3://咒术师
        cout<<"咒刃契约:每点力量额外提高2点法强，每点精神额外提高2点攻击。";
        break;
    case 4://神枪手
        cout<<"射手专注:每点洞察额外提高1点攻击、1点速度和1点命中。";
        break;
    case 5://影武士 
        cout<<"影裔血统:每点力量额外提高10点生命，每点精神额外提高10点法力。";
        break;
    }
    cout<<"\n选择属性提升: ";
    string list[6]= {"体力","智力","力量","精神","敏捷","洞察"};
    string explain[6];
    explain[0]="每点体力可以提高20点最大生命值和1点生命恢复。";
    explain[1]="每点智力可以提高20点最大法力值和1点法力恢复。";
    explain[2]="每点力量可以提高3点攻击和2点护甲。";
    explain[3]="每点精神可以提高3点法强和2点魔抗。";
    explain[4]="每点敏捷可以提高3点速度和4点闪避。";
    explain[5]="每点洞察可以提高3点暴击和4点命中。";
    switch(choose(6,list,explain))
    {
    case 0://体力
        vitality++;
        break;
    case 1://智力
        wit++;
        break;
    case 2://力量
        strength++;
        break;
    case 3://精神
        spirit++;
        break;
    case 4://敏捷
        agility++;
        break;
    case 5://洞察
        insight++;
        break;
    }
    display(0);
    gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
}
bool role::changeequ(equip equ)
{
    if(equiplist[equ.position].level)
    {
        string list[2]= {"否","是"};
        color(WHITE);
        cout<<"是否替换以下装备: ";
        CONSOLE_SCREEN_BUFFER_INFO xy;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
        cout<<"\n";
        equiplist[equ.position].showname(true);
        cout<<"\n";
        equiplist[equ.position].showexplain();
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
        switch(choose(2,list))
        {
        case 0:
            break;
        case 1:
            equiplist[equ.position]=equ;
            break;
        default:
            return false;
        }
    }
    else
    {
        string list[2]= {"是","否"};
        color(RED);
        cout<<"是否装备: ";
        color(WHITE);
        switch(choose(2,list))
        {
        case 0:
            equiplist[equ.position]=equ;
            break;
        case 1:
            break;
        default:
            return false;
        }
    }
    display(0);
    return true;
}
void role::showequip()
{
    for(int i=0; i<6; i++)
    {
        gotoxy(93,35+i);
        equiplist[i].showname(true);
    }
}
status role::battlestatus(bool who)
{
    status me;
    me.who=who;
    me.classes=classes;
    me.HPmax=100+vitality*20;
    me.HPrec=vitality;
    me.MPmax=20+wit*20;
    me.MPrec=wit;
    me.atk=5+strength*3;
    me.def=strength*2;
    me.abp=5+spirit*3;
    me.abr=spirit*2;
    me.spd=5+agility*3;
    me.avd=agility*4;
    me.crt=5+insight*3;
    me.hit=insight*4;
    //
    switch(classes)
    {
		case 0://不屈意志:每点体力额外提高10点生命和2点魔抗。
        me.HPmax+=vitality*10;
        me.abr+=vitality*2;
        break;
		case 1://智慧棱镜:每点智力额外提高1点法强和4点命中
        me.abp+=wit;
        me.hit+=wit*4;
        break;
		case 2://刺客本能:每点敏捷额外提高1点攻击和1点速度，每点洞察额外提高2点闪避
        me.atk+=agility;
        me.spd+=agility;
        me.avd+=insight*2;
        break;
		case 3://咒刃契约:每点力量额外提高2点法强，每点精神额外提高2点攻击
        me.abp+=strength*2;
        me.atk+=spirit*2;
        break;
		case 4://射手专注:每点洞察额外提高1点攻击,1点速度和1点命中 
        me.atk+=insight;
        me.spd+=insight;
        me.hit+=insight; 
        break;
        case 5://影裔血统:每点力量额外提高10点生命，每点精神额外提高10点法力
        me.HPmax+=strength*10;
        me.MPmax+=spirit*10;
        break;
    }
    //
    me.move=0;
    memset(me.attribute,0,sizeof(me.attribute));
    memset(me.debuff,0,sizeof(me.debuff));
    me.skill=skillnum;
    me.lv=level;
    memset(me.cd,0,8*sizeof(int));
    for(int i=0; i<6; i++)equiplist[i].paraset(&me);
    me.HP=me.HPmax;
    me.MP=me.MPmax;
    me.special=6;
    me.rec=true;
    return me;
}
//
int main(int argc,char* argv[])
{  
	char hstr[20];  
	int pid, problem, c;  
	int termstat; 
	if(argc==1)
    {
    	//
		setvbuf(stdout,NULL,_IONBF,0);
		if(_pipe(hpipe,256,O_BINARY)==-1)exit(1);
		itoa(hpipe[0],hstr,10);  
		if((pid=spawnl(P_NOWAIT,argv[0],argv[0],hstr,NULL))==-1)exit(1);
		//
	    system("mode 122,41");
	    system("title Eyizoha QQ779381838");
	    color(WHITE,BACKGROUNDCOLOR);
	    system("cls");
	    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	    CONSOLE_CURSOR_INFO cci;
	    GetConsoleCursorInfo(hOut,&cci);
	    cci.bVisible=false;
	    SetConsoleCursorInfo(hOut,&cci);
	    srand(time(NULL));
		srand(time(NULL)*magicnum[rand()%7]);
	    initialize();
	    while(1){start(menu());}
    }
	else
	{
		system("title BGM");
		int bgm;
		hpipe[0]=atoi(argv[1]);
		while(1)
		{
			if(read(hpipe[0],&bgm,sizeof(int)))
			{
				switch(bgm)
				{
					case -1:exit(0);
					case 0:PlaySound(NULL,NULL,PM);break;
					case 1:PlaySound(men,NULL,PM|SND_LOOP);break;
					case 2:PlaySound(wta,NULL,PM|SND_LOOP);break;
					case 3:PlaySound(bat,NULL,PM|SND_LOOP);break;
					case 4:PlaySound(bat2,NULL,PM|SND_LOOP);break;
					case 5:PlaySound(bat3,NULL,PM|SND_LOOP);break;
				}
			}
			Sleep(100);
		}
	}
}
void setbgm(int b)
{
	int bgm=b;
	write(hpipe[1],&bgm,sizeof(int));
}
void start(int t)
{
    if(t==0)
    {
        color(WHITE);
        system("cls");
        gotoxy(0,0);
        myrole.creat();
        if(myrole.save())
        {
            cout<<"\n角色保存成功！";
            Sleep(500);
        }
        else
        {
            cout<<"\n角色保存失败！";
            Sleep(500);
        }
    }
    else if(t==1)
    {
        string s,n;
        bool p=true;
        while(p)
        {
            color(WHITE);
            system("cls");
            gotoxy(0,0);
            cout<<"输入需要读取角色名字，回车确定(角色存档需放在本程序所在目录下): ";
            cin>>s;
            if(myrole.load(s))
            {
                n=myrole.name;
                if(s==n)
                {
                    cout<<"角色读取成功！";
                    p=false;
                    Sleep(500);
                }
                else
                {
                    cout<<"角色读取失败！";
                    Sleep(500);
                }
            }
            else
            {
                cout<<"角色读取失败！";
                Sleep(500);
            }
        }
    }
    else if(t==2)
    {
        pvp=true;
        string s,n;
        bool p=true;
        while(p)
        {
            color(WHITE);
            system("cls");
            gotoxy(0,0);
            cout<<"输入一号玩家的角色名字，回车确定(角色存档需放在本程序所在目录下): ";
            cin>>s;
            if(myrole.load(s))
            {
                n=myrole.name;
                if(s==n)
                {
                    cout<<"角色读取成功！";
                    p=false;
                    Sleep(500);
                }
                else
                {
                    cout<<"角色读取失败！";
                    Sleep(500);
                }
            }
            else
            {
                cout<<"角色读取失败！";
                Sleep(500);
            }
        }
        p=true;
        while(p)
        {
            color(WHITE);
            system("cls");
            gotoxy(0,0);
            cout<<"输入二号玩家的角色名字，回车确定(角色存档需放在本程序所在目录下): ";
            cin>>s;
            if(enemyrole.load(s))
            {
                n=enemyrole.name;
                if(s==n)
                {
                    cout<<"角色读取成功！";
                    p=false;
                    Sleep(500);
                }
                else
                {
                    cout<<"角色读取失败！";
                    Sleep(500);
                }
            }
            else
            {
                cout<<"角色读取失败！";
                Sleep(500);
            }
        }
    }
    setbgm(2);
    PlaySound(sta,NULL,PM);
    bool ctn;
    if(pvp)
    {
        system("cls");
        gotoxy(0,40);
        cout<<"按空格键开始战斗，ESC键返回菜单。";
        myrole.display(20);
        gotoxy(60,19);
        cout<<"VS";
        enemyrole.display(12);
        ctn=space_esc();
    }
    else
    {
        bool brk=true;
        while(brk)
        {
            system("cls");
            myrole.display(0);
            gotoxy(0,39);
            if(myrole.save())cout<<"进度保存成功！";
            else cout<<"进度保存失败！";
            gotoxy(0,40);
            cout<<"选择操作:";
            string list[4]= {"开始挑战","查看装备","重置属性点","返回菜单"};
            switch(choose(4,list))
            {
            case 0:
                ctn=true;
                brk=false;
                break;
            case 1:
                myrole.explainequip();
                break;
            case 2:
                myrole.resetpoint();
                break;
            case 3:
                ctn=false;
                brk=false;
                break;
            default:
                ctn=false;
                brk=false;
                break;
            }
        }
    }
    while(ctn)
    {
        if(!pvp)
        {
            enemyrole.createnemy(myrole.rank);
            if(battle())ctn=myrole.victory();
            else ctn=myrole.defeat();
        }
        if(pvp)
        {
            battle();
            system("cls");
            myrole.display(20);
            gotoxy(60,19);
            cout<<"VS";
            enemyrole.display(12);
            gotoxy(0,40);
            cout<<"按空格键重新战斗，ESC键返回菜单。";
            ctn=space_esc();
        }
    }
    pvp=false;
}
int menu()
{
	setbgm(1);
    drawmenu();
    int t=0,i;
    char ch=0;
    bool show=false;
    string p[4]= {" 新建角色 "," 读取角色 "," 玩家对战 "," 游戏说明 "};
    while(1)
    {

        color(WHITE,4);
        for(i=0; i<4; i++)
        {
            gotoxy(56,19+i);
            if(i==t)color(4,WHITE);
            cout<<p[i];
            color(WHITE,4);
        }
        ch=getch();
        if(ch==0)ch=getch();
        if(ch==UP)DEC(t,4);
        if(ch==DOWN)INC(t,4);
        if(ch==' '&&t!=3){PlaySound(cho,NULL,PM);return t;}
        if(ch==0x1B){setbgm(-1);exit(0);}
        //
        if(t==3&&!show)show=illustration(true);
        else if(t!=3&&show)show=illustration(false);
    }
}
bool illustration(bool p)
{
    if(p)
    {
    	PlaySound(dow,NULL,PM);
        color(WHITE,4);
        gotoxy(32,28);
        cout<<"游戏操作:                                                 ";
        gotoxy(32,29);
        cout<<"方向键选择，空格键确定，ESC键返回。                       ";
        gotoxy(32,30);
        cout<<"双方回合结束时有暂停，按空格可以继续。                    ";
        gotoxy(32,31);
        cout<<"注意:除了输入名字以外请勿开启输入法。                     ";
        gotoxy(32,32);
        cout<<"数据计算公式:                                             ";
        gotoxy(32,33);
        cout<<"最终物理伤害=基础伤害×40/(40+对方护甲)                   ";
        gotoxy(32,34);
        cout<<"最终魔法伤害=基础伤害×40/(40+对方魔抗)                   ";
        gotoxy(32,35);
        cout<<"最终真实伤害=基础伤害                                     ";
        gotoxy(32,36);
        cout<<"最终命中概率=基础命中概率×(100+己方命中)/(100+对方闪避)  ";
        gotoxy(32,37);
        cout<<"最终暴击概率=基础暴击概率×(100+己方暴击)/100             ";
        gotoxy(32,38);
        cout<<"暴击伤害=基础伤害×150%                                   ";
        color(7);
        gotoxy(58,24);
        cout<<"§  §";
        gotoxy(58,25);
        cout<<"§  §";
        gotoxy(58,26);
        cout<<"§  §";
        color(7,4);
        gotoxy(58,23);
        cout<<"※∞※";
        gotoxy(30,27);
        cout<<"┏━━━━━━━━━━━━━※∞※━━━━━━━━━━━━━┓";
        gotoxy(30,39);
        cout<<"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
        for(int i=28; i<=38; i++)
        {
            gotoxy(30,i);
            cout<<"┃";
            gotoxy(90,i);
            cout<<"┃";
        }
    }
    else
    {
    	PlaySound(upp,NULL,PM);
        color(7,4);
        gotoxy(54,23);
        cout<<"┗━━━━━┛";
        color(WHITE);
        gotoxy(58,24);
        cout<<"      ";
        gotoxy(58,25);
        cout<<"      ";
        gotoxy(58,26);
        cout<<"      ";
        for(int i=27; i<=39; i++)
        {
            gotoxy(30,i);
            cout<<"                                                              ";
        }
    }
    return p;
}
void drawmenu()
{
    system("cls");
    color(7,1);
    gotoxy(0,0);
    cout<<"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    gotoxy(0,1);
    cout<<"┃┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓┃";
    gotoxy(0,12);
    cout<<"┃┗━━━━━━━━━━━━━━━━━━━━━━━━━━┳BY-YZH┳━━━━━━━━━━━━━━━━━━━━━━━━━━┛┃";
    gotoxy(0,13);
    cout<<"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛※∞※┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
    for(int i=2; i<=11; i++)
    {
        gotoxy(0,i);
        cout<<"┃";
        gotoxy(2,i);
        cout<<"┃";
        gotoxy(120,i);
        cout<<"┃";
        gotoxy(118,i);
        cout<<"┃";
    }
    //
    color(7,4);
    gotoxy(4,2);
    cout<<"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    gotoxy(4,11);
    cout<<"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
    for(int i=3; i<=10; i++)
    {
        gotoxy(4,i);
        cout<<"┃";
        gotoxy(116,i);
        cout<<"┃";
    }
    color(YELLOW,4);
    gotoxy(6,3);
    cout<<" @@@            @@@     @@@@    @@@@        @@@    @@@@@@@@@         @@@@@@@@@      @@@@@@@@@      @@@@@@@@   ";
    gotoxy(6,4);
    cout<<" @@@@          @@@@      @@      @@@@@       @      @@               @@      @@     @@      @@   @@@      @@@ ";
    gotoxy(6,5);
    cout<<" @  @@        @  @@      @@      @   @@@     @      @@               @@      @@     @@      @@  @@          @ ";
    gotoxy(6,6);
    cout<<" @   @@      @   @@      @@      @     @@    @      @@@@@@@          @@@@@@@@       @@@@@@@@   @@             ";
    gotoxy(6,7);
    cout<<" @    @@    @    @@      @@      @      @@@  @      @@               @@   @@@       @@         @@             ";
    gotoxy(6,8);
    cout<<" @     @@  @     @@      @@      @       @@@ @      @@               @@    @@@      @@         @@@        @@@@";
    gotoxy(6,9);
    cout<<" @      @@@      @@      @@      @         @@@      @@               @@     @@@     @@          @@@        @@ ";
    gotoxy(6,10);
    cout<<"@@@      @      @@@@    @@@@    @@@        @@@@    @@@@@@@@@@       @@@@@    @@@@  @@@@@          @@@@@@@@@ @ ";
    //
    color(7);
    gotoxy(54,14);
    cout<<"    §  §    ";
    gotoxy(54,15);
    cout<<"    §  §    ";
    gotoxy(54,16);
    cout<<"    §  §    ";
    gotoxy(54,17);
    cout<<"    §  §    ";
    color(7,4);
    gotoxy(54,18);
    cout<<"┏━※∞※━┓";
    gotoxy(54,19);
    cout<<"┃          ┃";
    gotoxy(54,20);
    cout<<"┃          ┃";
    gotoxy(54,21);
    cout<<"┃          ┃";
    gotoxy(54,22);
    cout<<"┃          ┃";
    gotoxy(54,23);
    cout<<"┗━━━━━┛";
    //
    color(7);
    gotoxy(0,18);
    cout<<"                ,$               ∧";
    gotoxy(0,19);
    cout<<"               I+8?             // ";
    gotoxy(0,20);
    cout<<"              NI $Z            //  ";
    gotoxy(0,21);
    cout<<"              =:N,Z+          //   ";
    gotoxy(0,22);
    cout<<"               +I?+          //    ";
    gotoxy(0,23);
    cout<<"              ?~D8ZI        //     ";
    gotoxy(0,24);
    cout<<"        Z   ,$7=I77?Z$     //      ";
    gotoxy(0,25);
    cout<<"       NID8 =77=I7II77    //       ";
    gotoxy(0,26);
    cout<<"      $$ZO8:7,$I=?$I$7   //        ";
    gotoxy(0,27);
    cout<<"      IZOOI$  ?7?++?77ZO~,=        ";
    gotoxy(0,28);
    cout<<"       =OOO    ?+++?  =7I7 +:      ";
    gotoxy(0,29);
    cout<<"              7I7II$    N$         ";
    gotoxy(0,30);
    cout<<"              ?~I+?I?   +          ";
    gotoxy(0,31);
    cout<<"             ==??Z?I?              ";
    gotoxy(0,32);
    cout<<"              ++? ?+~              ";
    gotoxy(0,33);
    cout<<"              ?I  IO               ";
    gotoxy(0,34);
    cout<<"              :?  ?+               ";
    gotoxy(0,35);
    cout<<"             :?    ?I              ";
    gotoxy(0,36);
    cout<<"             ~I    ??              ";
    gotoxy(0,37);
    cout<<"             =      =              ";
    gotoxy(0,38);
    cout<<"             7      ?+,,,          ";
    gotoxy(0,39);
    cout<<"            I7,:::~?I=$$~:,        ";
    gotoxy(0,40);
    cout<<"           :$?=,                   ";
    //
    gotoxy(85,18);
    cout<<"∧                Z,              ";
    gotoxy(85,19);
    cout<<" \\\\              ~8+$           ";
    gotoxy(85,20);
    cout<<"  \\\\             Z7 ?M          ";
    gotoxy(85,21);
    cout<<"   \\\\           +Z=O:=          ";
    gotoxy(85,22);
    cout<<"    \\\\           +?I+           ";
    gotoxy(85,23);
    cout<<"     \\\\         ~OOD=?          ";
    gotoxy(85,24);
    cout<<"      \\\\      ZZI7$7=77    Z    ";
    gotoxy(85,25);
    cout<<"       \\\\     7ZII77+7I= ODIN,  ";
    gotoxy(85,26);
    cout<<"        \\\\    I$I7?~I7 I:OOZ7$  ";
    gotoxy(85,27);
    cout<<"        =,~OZZI7?++?$I  Z?OOZI    ";
    gotoxy(85,28);
    cout<<"        :+ ZI7=  ?+++?   OOO=     ";
    gotoxy(85,29);
    cout<<"           8N    $I7I77           ";
    gotoxy(85,30);
    cout<<"            +   ?????~?           ";
    gotoxy(85,31);
    cout<<"                ?I?Z?~?=          ";
    gotoxy(85,32);
    cout<<"                ,+? ?++           ";
    gotoxy(85,33);
    cout<<"                 O7  II           ";
    gotoxy(85,34);
    cout<<"                 +?  ?::          ";
    gotoxy(85,35);
    cout<<"                I?:   I,          ";
    gotoxy(85,36);
    cout<<"                ??    I~          ";
    gotoxy(85,37);
    cout<<"                +=     =          ";
    gotoxy(85,38);
    cout<<"            ,,,I?      7          ";
    gotoxy(85,39);
    cout<<"          ,:~$$=I?~:::,7I         ";
    gotoxy(85,40);
    cout<<"                     ,=?$:       ";
    //
}
void gotoxy(int x,int y)
{
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void color(int c)
{
    HANDLE hConsole=GetStdHandle((STD_OUTPUT_HANDLE));
    SetConsoleTextAttribute(hConsole,BACKGROUNDCOLOR*16+c);
}
void color(int c,int b)
{
    HANDLE hConsole=GetStdHandle((STD_OUTPUT_HANDLE));
    SetConsoleTextAttribute(hConsole,b*16+c);
}
bool space_esc()
{
    char ch;
    while(1)
    {
        ch=getch();
        if(ch==' ')return true;
        else if(ch==0x1B)return false;
    }
}
void initialize()
{
    sl[0][0].name="攻击";
    sl[0][0].explain="无消耗,无冷却,命中80%,暴击20%:对敌方进行普通攻击，造成100%攻击力的物理伤害。";
    sl[0][0].spend=0;
    sl[0][0].cd=0;
    sl[0][0].sp=w_0attack;

    sl[0][1].name="冲锋预备";
    sl[0][1].explain="消耗30MP,冷却2回合:准备进行冲锋，提升200%的攻击2回合、清除减速效果并增加80%行动条。";
    sl[0][1].spend=30;
    sl[0][1].cd=2;
    sl[0][1].sp=w_1charge;

    sl[0][2].name="缴械";
    sl[0][2].explain="消耗40MP,冷却3回合,命中100%:破坏敌方的武器与护甲，降低敌方60%的攻击与护甲4回合。";
    sl[0][2].spend=40;
    sl[0][2].cd=3;
    sl[0][2].sp=w_2disarm;

    sl[0][3].name="磐石之力";
    sl[0][3].explain="消耗20MP,冷却4回合:以坚如磐石的意志强化自身，提升200%护甲与魔抗6回合并清除所有减益状态。";
    sl[0][3].spend=20;
    sl[0][3].cd=4;
    sl[0][3].sp=w_3stone;

    sl[0][4].name="致残打击";
    sl[0][4].explain="消耗50MP,冷却3回合,命中80%,暴击20%:攻击敌方弱点来重创敌方的行动能力，造成160%攻击力的物理伤害，施加4(暴击:6)回合减速40%和4(暴击:6)回合伤害为25%攻击力的流血。";
    sl[0][4].spend=50;
    sl[0][4].cd=3;
    sl[0][4].sp=w_4cripple;

    sl[0][5].name="盾牌猛击";
    sl[0][5].explain="消耗40MP,冷却5回合,命中100%,暴击50%:使用盾牌猛击敌方，对敌方造成400%护甲的物理伤害并击退50%(暴击:75%)的行动条，若敌方行动条触底则眩晕其1回合。";
    sl[0][5].spend=40;
    sl[0][5].cd=5;
    sl[0][5].sp=w_5shieldhit;

    sl[0][6].name="血气唤醒";
    sl[0][6].explain="无消耗,冷却5回合:通过古老的法术唤醒血气强化并治愈自身，每损失1%的生命值便提高2%的攻击4回合，随后每有1点法强便恢复2%的已损失生命值。";
    sl[0][6].spend=0;
    sl[0][6].cd=5;
    sl[0][6].sp=w_6bloodwake;

    sl[0][7].name="雷霆毁灭";
    sl[0][7].explain="消耗20%HP,冷却1回合,命中80%,暴击40%:消耗自身生命值来释放雷霆毁灭之力重创敌方，对敌方造成200%消耗生命值的真实伤害，未命中时返还消耗生命值。";
    sl[0][7].spend=0;
    sl[0][7].cd=1;
    sl[0][7].sp=w_7rage;
    //
    sl[1][0].name="攻击";
    sl[1][0].explain="无消耗,无冷却,命中80%,暴击20%:对敌方进行普通攻击，造成100%攻击力的物理伤害。";
    sl[1][0].spend=0;
    sl[1][0].cd=0;
    sl[1][0].sp=m_0attack;

    sl[1][1].name="武器附魔";
    sl[1][1].explain="消耗40MP,冷却2回合:为武器附上魔法，提升相当于法强的攻击力，持续3回合，该技能释放完后立刻进行一次攻击。";
    sl[1][1].spend=40;
    sl[1][1].cd=2;
    sl[1][1].sp=m_1enchants;

    sl[1][2].name="风暴盾";
    sl[1][2].explain="消耗60MP,冷却3回合:用风暴笼罩自身形成护盾，提高30%的速度同时每有1点法强便提高1%的护甲，持续5回合。";
    sl[1][2].spend=60;
    sl[1][2].cd=3;
    sl[1][2].sp=m_2stormshieldl;

    sl[1][3].name="暴风雪";
    sl[1][3].explain="消耗80MP,冷却4回合,命中80%,暴击20%:召唤暴风雪攻击敌方，造成6次40%法强的魔法伤害，每次伤害独立计算命中与暴击，每次命中还会施加1回合的冰冻效果(降低40%速度和80%闪避)。";
    sl[1][3].spend=80;
    sl[1][3].cd=4;
    sl[1][3].sp=m_3snowstorm;

    sl[1][4].name="冰枪术";
    sl[1][4].explain="消耗50MP,无冷却,命中80%,暴击30%:向敌方发射一支法力凝结的冰枪，造成150%法强的魔法伤害，若目标被冰冻则伤害翻倍。";
    sl[1][4].spend=50;
    sl[1][4].cd=0;
    sl[1][4].sp=m_4icelance;

    sl[1][5].name="心灵震爆";
    sl[1][5].explain="消耗40MP,冷却5回合,命中200%,暴击50%:用魔法直击敌方心灵，造成120%法强的真实伤害，并降低敌方50%的法强与魔抗3回合，该技能暴击时将眩晕敌方1回合。";
    sl[1][5].spend=40;
    sl[1][5].cd=5;
    sl[1][5].sp=m_5mindblast;

    sl[1][6].name="冥想";
    sl[1][6].explain="消耗100MP,冷却5回合:进行一次冥想，每有2点法强便恢复1%的最大生命值同时减少所有技能1回合的冷却时间。";
    sl[1][6].spend=100;
    sl[1][6].cd=5;
    sl[1][6].sp=m_6muse;

    sl[1][7].name="法力燃烧";
    sl[1][7].explain="消耗20%MP,冷却3回合,命中100%,暴击20%:消耗自身法力值引燃敌方法力，燃烧敌方200%消耗法力值的法力并造成200%消耗法力值的魔法伤害，同时施加2回合伤害为50%消耗法力值燃烧。";
    sl[1][7].spend=0;
    sl[1][7].cd=3;
    sl[1][7].sp=m_7manaburn;
    //
    sl[2][0].name="攻击";
    sl[2][0].explain="无消耗,无冷却,命中80%,暴击20%:对敌方进行普通攻击，造成100%攻击力的物理伤害。";
    sl[2][0].spend=0;
    sl[2][0].cd=0;
    sl[2][0].sp=a_0attack;

    sl[2][1].name="刺杀";
    sl[2][1].explain="消耗30MP,冷却3回合,命中100%,暴击40%:对敌方进行一次致命攻击，造成160%攻击力的物理伤害，敌方每损失1%生命值都会提升该技能3%的伤害。";
    sl[2][1].spend=30;
    sl[2][1].cd=3;
    sl[2][1].sp=a_1assassinate;

    sl[2][2].name="致盲粉";
    sl[2][2].explain="消耗40MP,冷却6回合,命中80%:向敌方投掷致盲粉雾弹使敌方致盲，降低敌方50%的命中和暴击4回合。";
    sl[2][2].spend=40;
    sl[2][2].cd=6;
    sl[2][2].sp=a_2blindingpowder;

    sl[2][3].name="潜行";
    sl[2][3].explain="无消耗,冷却5回合:进入潜行状态，提升300%的闪避1回合、降低20%速度1回合、提高100%暴击2回合并清除所有症状。";
    sl[2][3].spend=0;
    sl[2][3].cd=5;
    sl[2][3].sp=a_3sneak;

    sl[2][4].name="淬毒匕首";
    sl[2][4].explain="消耗50MP,冷却4回合,命中80%,暴击30%:向敌方投掷一把淬毒匕首，造成相当于敌方当前生命值20%的物理伤害并施加4回合伤害为其最大生命值5%(每点法强额外提升0.2%)的中毒。";
    sl[2][4].spend=50;
    sl[2][4].cd=4;
    sl[2][4].sp=a_4poisondagger;

    sl[2][5].name="闷棍";
    sl[2][5].explain="消耗20MP,冷却8回合,命中100%,暴击10%:出其不意地重击敌方弱点，降低敌方40%的护甲3回合并使其眩晕1(暴击:2)回合。";
    sl[2][5].spend=20;
    sl[2][5].cd=8;
    sl[2][5].sp=a_5stickstrike;

    sl[2][6].name="虚弱药剂";
    sl[2][6].explain="消耗40MP,冷却6回合,命中80%:向敌方投掷一瓶虚弱药剂使得敌方虚弱4回合，虚弱状态时降低50%的攻击与法强。";
    sl[2][6].spend=40;
    sl[2][6].cd=6;
    sl[2][6].sp=a_6weakagent;

    sl[2][7].name="致命节奏";
    sl[2][7].explain="消耗40MP,冷却2回合:对敌方进行一次攻击，本回合内所有的攻击结束后都进行一次50%概率的连击判定，判定成功时追加一次攻击，判定失败时重新进行判定直到累计判定失败3次。";
    sl[2][7].spend=40;
    sl[2][7].cd=2;
    sl[2][7].sp=a_7fatalrhythm;
    //
    sl[3][0].name="攻击";
    sl[3][0].explain="无消耗,无冷却,命中80%,暴击20%:对敌方进行普通攻击，造成100%攻击力的物理伤害。";
    sl[3][0].spend=0;
    sl[3][0].cd=0;
    sl[3][0].sp=c_0attack;

    sl[3][1].name="神锋咒";
    sl[3][1].explain="消耗50MP,冷却3回合,命中100%,暴击25%:咒语召唤无形的利刃瞬间切割敌方，施加4(暴击:6)回合伤害为100%攻击的流血。";
    sl[3][1].spend=50;
    sl[3][1].cd=3;
    sl[3][1].sp=c_1sectumsempra;

    sl[3][2].name="烈火咒";
    sl[3][2].explain="消耗50MP,冷却3回合,命中100%,暴击25%:咒语召唤炽热的火焰猛烈席卷敌方，施加4(暴击:6)回合伤害为100%法强的燃烧。";
    sl[3][2].spend=50;
    sl[3][2].cd=3;
    sl[3][2].sp=c_2blaze;

    sl[3][3].name="五毒咒";
    sl[3][3].explain="消耗50MP,冷却3回合,命中100%,暴击25%:咒语召唤恐怖的剧毒缓慢侵蚀敌方，施加4(暴击:6)回合伤害为50%攻击+50%法强的中毒。";
    sl[3][3].spend=50;
    sl[3][3].cd=3;
    sl[3][3].sp=c_3fivepoisons;

    sl[3][4].name="守护咒";
    sl[3][4].explain="消耗40MP,冷却4回合:咒语守护自身，提升200%速度1回合，同时根据敌方攻击与法强的比例，每有1点法强便自适应地提升2%的护甲或魔抗，持续6回合。";
    sl[3][4].spend=40;
    sl[3][4].cd=4;
    sl[3][4].sp=c_4daemon;

    sl[3][5].name="增幅咒";
    sl[3][5].explain="消耗20MP,冷却1回合:咒语增幅敌方的所有症状，使敌方所有症状持续回合+1。";
    sl[3][5].spend=20;
    sl[3][5].cd=1;
    sl[3][5].sp=c_5increase;

    sl[3][6].name="夺魂咒";
    sl[3][6].explain="无消耗,冷却6回合,命中100%:咒语侵夺敌方灵魂，造成其最大生命值20%的真实伤害并为自身恢复等于该值的生命值，同时消耗其最大法力值20%的法力并为自身恢复等于该值的法力值。";
    sl[3][6].spend=0;
    sl[3][6].cd=6;
    sl[3][6].sp=c_6imperio;

    sl[3][7].name="万咒覆灭引";
    sl[3][7].explain="消耗100MP,冷却7回合:引导施加在敌方身上的所有咒语效果，清除敌方所有症状并将所有症状将产生伤害瞬间施加于敌方。";
    sl[3][7].spend=100;
    sl[3][7].cd=7;
    sl[3][7].sp=c_7summarycurse;
    //
    sl[4][0].name="攻击/填装";
    sl[4][0].explain="无消耗,无冷却,命中80%,暴击20%:向敌方发射一发子弹，造成100%攻击力的物理伤害。弹轮中无子弹时将进行填装，将弹轮填满。";
    sl[4][0].spend=0;
    sl[4][0].cd=0;
    sl[4][0].sp=s_0attack;
    bulletspend[0]=0;

    sl[4][1].name="快速拔枪";
    sl[4][1].explain="消耗30MP,冷却3回合:快速拔枪对敌方进行一次攻击，随后进行一个额外回合。";
    sl[4][1].spend=30;
    sl[4][1].cd=3;
    sl[4][1].sp=s_1quickfire;
    bulletspend[1]=1;

    sl[4][2].name="精准射击";
    sl[4][2].explain="消耗40MP,冷却4回合,命中100%,暴击20%:向敌方要害进行一次精准射击，造成160%攻击力的物理伤害，每有2点命中都会提升该技能1%的伤害。";
    sl[4][2].spend=40;
    sl[4][2].cd=4;
    sl[4][2].sp=s_2deadeyeshoot;
    bulletspend[2]=1;

    sl[4][3].name="战术反制";
    sl[4][3].explain="无消耗,冷却8回合,命中80%:对敌方进行一次战术反制，清空敌方的行动条并为己方增加清空值相等数值的行动条。";
    sl[4][3].spend=0;
    sl[4][3].cd=8;
    sl[4][3].sp=s_3tacticalcounter;
    bulletspend[3]=0;

    sl[4][4].name="拦截射击";
    sl[4][4].explain="消耗60MP,冷却6回合,命中80%,暴击20%:向敌方连续发射三发子弹，造成3次100%攻击力的物理伤害，每发子弹独立计算命中与暴击，若三发子弹全部命中则眩晕敌方1回合。";
    sl[4][4].spend=60;
    sl[4][4].cd=6;
    sl[4][4].sp=s_4interceptingshoot;
    bulletspend[4]=3;

    sl[4][5].name="快速填装";
    sl[4][5].explain="消耗20MP,冷却6回合:进行一次快速填装，将弹轮填满，随后进行一个额外回合。";
    sl[4][5].spend=20;
    sl[4][5].cd=6;
    sl[4][5].sp=s_5quickreload;
    bulletspend[5]=0;

    sl[4][6].name="死亡标记";
    sl[4][6].explain="消耗40MP,冷却6回合,命中80%:对敌方施加一个死亡标记，降低其80%的护甲与魔抗2回合。";
    sl[4][6].spend=40;
    sl[4][6].cd=6;
    sl[4][6].sp=s_6deathmarker;
    bulletspend[6]=0;

    sl[4][7].name="暴雨疾射";
    sl[4][7].explain="消耗60MP,冷却8回合,命中60%,暴击10%:快速向敌方发射出弹轮中所有的子弹，每发子弹造成150%攻击力的物理伤害，每发子弹独立计算命中与暴击。";
    sl[4][7].spend=60;
    sl[4][7].cd=8;
    sl[4][7].sp=s_7stormshoot;
    bulletspend[7]=1;
    //
    sl[5][0].name="攻击";
    sl[5][0].explain="无消耗,无冷却,命中80%,暴击10%:对敌方进行普通攻击，造成100%攻击力的物理伤害。";
    sl[5][0].spend=0;
    sl[5][0].cd=0;
    sl[5][0].sp=d_0attack;
    
    sl[5][1].name="影刃";
    sl[5][1].explain="消耗50MP,冷却4回合:以暗影缠绕太刀，提高150%的攻击和命中5回合。";
    sl[5][1].spend=50;
    sl[5][1].cd=4;
    sl[5][1].sp=d_1shadowblade;
    
    sl[5][2].name="诅咒之影";
    sl[5][2].explain="消耗20MP,冷却4回合,命中80%:随机转移自身两个减益状态到暗影中并以暗影捕捉敌方影子，命中时将减益状态转移给敌方。";
    sl[5][2].spend=20;
    sl[5][2].cd=4;
    sl[5][2].sp=d_2curseshadow;
    
    sl[5][3].name="三段斩";
    sl[5][3].explain="消耗30MP,冷却3回合:快速对敌方进行连续三次攻击。";
    sl[5][3].spend=30;
    sl[5][3].cd=3;
    sl[5][3].sp=d_3triplechop;
    
    sl[5][4].name="遁入暗影";
    sl[5][4].explain="消耗50%MP,冷却4回合:消耗大量法力值形成暗影笼罩自身，提高400%闪避1回合并恢复200%消耗法力值的生命值。";
    sl[5][4].spend=0;
    sl[5][4].cd=4;
    sl[5][4].sp=d_4intoshadow;
    
    sl[5][5].name="影缚";
    sl[5][5].explain="消耗40MP,冷却4回合,命中100%:以影子缠绕敌方阻碍敌方施法，使其攻击以外的所有技能冷却计时+2。";
    sl[5][5].spend=40;
    sl[5][5].cd=4;
    sl[5][5].sp=d_5shadowdurance;
    
    sl[5][6].name="暗影血祭";
    sl[5][6].explain="消耗50%HP,冷却7回合:消耗大量生命值献祭暗影强化自身，提高40%消耗生命值的护甲和魔抗以及60%消耗生命值的法强，持续7回合。";
    sl[5][6].spend=0;
    sl[5][6].cd=7;
    sl[5][6].sp=d_6bloodsacrifice;
    
    sl[5][7].name="影剑阵";
    sl[5][7].explain="消耗120MP,冷却6回合,命中80%,暴击10%:召唤8把暗影之剑攻击敌方，每把影剑独立计算命中与暴击，影剑命中时造成25%法强的真实伤害并附加4回合的对应属性25%减益效果。";
    sl[5][7].spend=120;
    sl[5][7].cd=6;
    sl[5][7].sp=d_7shadowswordcircle;
}
bool hitthat(double p)
{
    if(rand()<=p*RAND_MAX)return true;
    else return false;
}
void drawbar(double p)
{
    int i;
    if(p>=0.99999999)
    {
        for(i=10; i--; i>0)cout<<"█";
        return;
    }
    int a;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    for(i=10; i--; i>0)cout<<"  ";
    gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
    a=(int)(p*10);
    for(i=a; i--; i>0)cout<<"█";
    if(a==10)return;
    i=(int)((p*10-(int)(p*10))*8);
    switch(i)
    {
    case 0:
        cout<<"  ";
        break;
    case 1:
        cout<<"▏";
        break;
    case 2:
        cout<<"▎";
        break;
    case 3:
        cout<<"▍";
        break;
    case 4:
        cout<<"▌";
        break;
    case 5:
        cout<<"▋";
        break;
    case 6:
        cout<<"▊";
        break;
    case 7:
        cout<<"▉";
        break;
    }
    for(i=9-a; i--; i>0)cout<<"  ";
}
void drawmvbar(double p,bool who)
{
    color(CYAN);
    int i,a;
    char d[5];
    if(p>=0.99999999)p=1;
    if(who)
    {
        if(p<lastmvp)
        {
            gotoxy(96,2);
            cout<<"                    ";
            gotoxy(118,2);
            cout<<"    ";
        }
        itoa((int)(p*100),d,10);
        gotoxy(118,2);
        cout<<d<<'%';
        lastmvp=p;
        gotoxy(96,2);
        a=(int)(p*10);
        for(i=a; i--; i>0)cout<<"█";
        if(a==10)return;
        i=(int)((p*10-(int)(p*10))*8);
        switch(i)
        {
        case 0:
            cout<<"  ";
            break;
        case 1:
            cout<<"▏";
            break;
        case 2:
            cout<<"▎";
            break;
        case 3:
            cout<<"▍";
            break;
        case 4:
            cout<<"▌";
            break;
        case 5:
            cout<<"▋";
            break;
        case 6:
            cout<<"▊";
            break;
        case 7:
            cout<<"▉";
            break;
        }
    }
    else
    {
        if(p<lastmve)
        {
            gotoxy(96,4);
            cout<<"                    ";
            gotoxy(118,4);
            cout<<"    ";
        }
        itoa((int)(p*100),d,10);
        gotoxy(118,4);
        cout<<d<<'%';
        lastmve=p;
        gotoxy(96,4);
        a=(int)(p*10);
        for(i=a; i--; i>0)cout<<"█";
        if(a==10)return;
        i=(int)((p*10-(int)(p*10))*8);
        switch(i)
        {
        case 0:
            cout<<"  ";
            break;
        case 1:
            cout<<"▏";
            break;
        case 2:
            cout<<"▎";
            break;
        case 3:
            cout<<"▍";
            break;
        case 4:
            cout<<"▌";
            break;
        case 5:
            cout<<"▋";
            break;
        case 6:
            cout<<"▊";
            break;
        case 7:
            cout<<"▉";
            break;
        }
    }
}
void writenum(int p,int f)
{
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    color(WHITE);
    if(p<f)color(RED);
    if(p>f)color(GREEN);
    cout<<"      ";
    gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
    cout<<p;
}
int choose(int n,string* p)
{
    int t=0,i=0;
    char ch=0;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    while(1)
    {
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
        for(i=0; i<n; i++)
        {
            if(i==t)color(BACKGROUNDCOLOR,WHITE);
            cout<<p[i];
            color(WHITE,BACKGROUNDCOLOR);
            cout<<' ';
        }
        color(WHITE);
        ch=getch();
        if(ch==0)ch=getch();
        if(ch==LEFT)DEC(t,n);
        if(ch==RIGHT)INC(t,n);
        if(ch==' '){PlaySound(cho,NULL,PM);return t;}
        if(ch==0x1B)return -1;
    }
}
int choose(int n,string* p,string* explain,int k)
{
    int t=k,i=0;
    char ch=0;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    while(1)
    {
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
        for(i=0; i<n; i++)
        {
            if(i==t)color(BACKGROUNDCOLOR,WHITE);
            cout<<p[i];
            color(WHITE,BACKGROUNDCOLOR);
            cout<<' ';
        }
        gotoxy(0,xy.dwCursorPosition.Y+1);
        cout<<"                                                                                                                          ";
        cout<<"                                                                                                                          ";
        color(13);
        gotoxy(0,xy.dwCursorPosition.Y+1);
        cout<<explain[t];
        color(WHITE);
        ch=getch();
        if(ch==0)ch=getch();
        if(ch==LEFT)DEC(t,n);
        if(ch==RIGHT)INC(t,n);
        if(ch==' '){PlaySound(cho,NULL,PM);return t;}
    }
}
int skillchoose(status* p,int n,string* name,string* explain)
{
    int t=0,i=0;
    char ch=0;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    while(1)
    {
        gotoxy(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
        for(i=0; i<n; i++)
        {
            if(i==t)color(BACKGROUNDCOLOR,WHITE);
            cout<<name[i];
            if(p->cd[i])cout<<'('<<p->cd[i]<<')';
            color(WHITE,BACKGROUNDCOLOR);
            cout<<' ';
        }
        gotoxy(0,xy.dwCursorPosition.Y+1);
        cout<<"                                                                                                                          ";
        cout<<"                                                                                                                          ";
        color(13);
        gotoxy(0,xy.dwCursorPosition.Y+1);
        cout<<explain[t];
        color(WHITE);
        ch=getch();
        if(ch==0)ch=getch();
        if(ch==LEFT)DEC(t,n);
        if(ch==RIGHT)INC(t,n);
        if(ch==' ')return t;
        if(ch==0x1B)return -1;
    }
}
void drawboard()
{
    color(WHITE);
    system("cls");
    gotoxy(0,0);
    cout<<"敌方:                                   ┃攻击:      护甲:      法强:      魔抗:      ┃行动条";
    gotoxy(0,1);
    cout<<"┏━━━━━━━━━━┓                ┃速度:      闪避:      暴击:      命中:      ┃      ┏━━━━━━━━━━┓";
    gotoxy(0,2);
    cout<<"┃                    ┃HP:             ┃被动技能:                                   ┃我方: ┃                    ┃";
    gotoxy(0,3);
    cout<<"┣━━━━━━━━━━┫                ┃                                            ┃      ┣━━━━━━━━━━┫";
    gotoxy(0,4);
    cout<<"┃                    ┃MP:             ┃                                            ┃敌方: ┃                    ┃";
    gotoxy(0,5);
    cout<<"┗━━━━━━━━━━┛                ┃                                            ┃      ┗━━━━━━━━━━┛";
    gotoxy(0,6);
    cout<<"━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━";
    gotoxy(0,7);
    cout<<"状态: ";
    gotoxy(0,8);
    cout<<"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    for(int i=9; i<=27; i++)
    {
        gotoxy(60,i);
        cout<<"┃";
    }
    gotoxy(0,28);
    cout<<"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    gotoxy(0,29);
    cout<<"技能:";
    gotoxy(0,32);
    cout<<"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    gotoxy(0,33);
    cout<<"状态: ";
    gotoxy(0,34);
    cout<<"━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━";
    gotoxy(0,35);
    cout<<"我方:                                   ┃攻击:      护甲:      法强:      魔抗:      ┃武器:";
    gotoxy(0,36);
    cout<<"┏━━━━━━━━━━┓                ┃速度:      闪避:      暴击:      命中:      ┃头部:";
    gotoxy(0,37);
    cout<<"┃                    ┃HP:             ┃被动技能:                                   ┃颈部:";
    gotoxy(0,38);
    cout<<"┣━━━━━━━━━━┫                ┃                                            ┃躯干:";
    gotoxy(0,39);
    cout<<"┃                    ┃MP:             ┃                                            ┃手部:";
    gotoxy(0,40);
    cout<<"┗━━━━━━━━━━┛                ┃                                            ┃足部:";
}
bool battle()
{
	setbgm(rand()%3+3);
    drawboard();
    //
    player=myrole.battlestatus(true);
    enemy=enemyrole.battlestatus(false);
    //
    mgeline=9;
    row=0;
    lastmvp=0;
    lastmve=0;
    esc=false;
    //
    string s;
    showskill();
    myrole.showequip();
    showbar(player);
    showbar(enemy);
    showsta(player);
    showsta(enemy);
    showmessage("战斗开始！");
    //技能
    if(player.classes==1&&player.lv>=10)m_phaseblink(&player);
    if(enemy.classes==1&&enemy.lv>=10)m_phaseblink(&enemy);
    //装备
    myrole.returnequ(1).effect(&player);
    enemyrole.returnequ(1).effect(&enemy);
    //
    while(1)
    {
        turnend(turnstart(whoseturn(&player,&enemy)));
        if(esc||!space_esc()){setbgm(2);return false;}
        //
        if(player.HP<=0)myrole.returnequ(2).effect(&player);
        if(enemy.HP<=0)enemyrole.returnequ(2).effect(&enemy);
        //
        if(player.HP<=0)
        {
            color(WHITE);
            s=myrole.name;
            showmessage(s+"已被击败！");
            getch();
            setbgm(2);
            return false;
        }
        if(enemy.HP<=0)
        {
            color(WHITE);
            s=enemyrole.name;
            showmessage(s+"已被击败！");
            getch();
            setbgm(2);
            return true;
        }
    }
}
void showmessage(string s)
{
    //color(WHITE);
    if(mgeline>27)
    {
        row=(row+1)%2;
        while(mgeline>9)
        {
            mgeline--;
            gotoxy(62*row,mgeline);
            cout<<"                                                            ";
        }
    }
    gotoxy(62*row,mgeline);
    cout<<s;
    mgeline++;
}
status* whoseturn(status* player,status* enemy)
{
    double *p,*e;
    int ps,es;
    double interval;
    p=&player->move;
    e=&enemy->move;
    ps=player->spd;
    es=enemy->spd;
    interval=0.02/(ps>=es?ps:es);
    drawmvbar(*p,true);
    drawmvbar(*e,false);
    while(1)
    {
        if(*p>=0.99999999&&*e>=0.99999999)
        {
            if(hitthat(0.5))
            {
                *p=0;
                return player;
            }
            else
            {
                *e=0;
                return enemy;
            }
        }
        if(*p>=0.99999999)
        {
            *p=0;
            return player;
        }
        if(*e>=0.99999999)
        {
            *e=0;
            return enemy;
        }
        *p+=ps*interval;
        *e+=es*interval;
        drawmvbar(*p,true);
        drawmvbar(*e,false);
        Sleep(10);
    }
}
status* turnstart(status* p)
{
    color(8);
    showmessage("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    int i;
    string s;
    bool hpr=true,mpr=true;
    //
    status f;
    if(p->who)
    {
        f=myrole.battlestatus(true);
        s=myrole.name;
    }
    else
    {
        f=enemyrole.battlestatus(false);
        s=enemyrole.name;
    }
    color(YELLOW);
    showmessage(s+"回合开始！");
    //DEBUFF
    for(i=0; i<3; i++) //流血燃烧中毒
    {
        if(p->debuff[i].duration)
        {
            p->debuff[i].duration--;
            switch(i)
            {
            case 0:
                color(WHITE);
                showmessage(s+"流血，受到物理伤害。");
                damage(p,AD,-p->debuff[i].ratio,HPbar);
                hpr=false;
                break;
            case 1:
                color(WHITE);
                showmessage(s+"燃烧，受到魔法伤害。");
                damage(p,AP,-p->debuff[i].ratio,HPbar);
                mpr=false;
                break;
            case 2:
                color(WHITE);
                showmessage(s+"中毒，受到真实伤害。");
                damage(p,RE,-p->debuff[i].ratio,HPbar);
                break;
            }
        }
    }
    //
    //死亡
    if(p->HP<=0)return p;
    //自动恢复
    if(hpr)damage(p,RE,p->HPrec,HPbar);
    else
    {
        color(WHITE);
        showmessage(s+"流血，本回合无法自然恢复生命。");
    }
    if(mpr)damage(p,RE,p->MPrec,MPbar);
    else
    {
        color(WHITE);
        showmessage(s+"燃烧，本回合无法自然恢复法力。");
    }
    //
    //属性加减
    for(i=0; i<8; i++) //攻防强抗速闪暴命
        if(p->attribute[i].duration)p->attribute[i].duration--;
    dealbuff(p);
    //眩晕
    if(p->debuff[3].duration)//眩晕
    {
        p->debuff[3].duration--;
        color(WHITE);
        showmessage(s+"被眩晕，本回合无法行动。");
        showbuff(*p);
        return p;
    }
    //equip
    if(p->who)myrole.returnequ(0).effect(p);
    else enemyrole.returnequ(0).effect(p);
    if(player.HP<=0||enemy.HP<=0)return p;
    //操作区
    if(p->who||pvp)esc=operate(p);
    else enemyrole.opp(p);
    //
    return p;
}
void turnend(status* p)
{
    if(esc)return;
    if(player.HP<=0||enemy.HP<=0)return;
    //清除操作面板
    if(p->who||pvp)
    {
        gotoxy(5,29);
        cout<<"                                                                                                                     ";
        cout<<"                                                                                                                          ";
        cout<<"                                                                                                                          ";
    }
    //技能
    if(p->classes==2&&p->lv>=10)a_preparation(p);
    if(p->classes==3&&p->lv>=4)c_vicious(p);
    if(p->classes==3&&p->lv>=10)c_boundary(p);
    if(p->classes==5&&p->lv>=10)d_shadowstep(p);
    //-cd
    for(int i=0; i<8; i++)if(p->cd[i])p->cd[i]--;
    //equip
    for(int i=3; i<6; i++)
    {
        if(p->who)myrole.returnequ(i).effect(p);
        else enemyrole.returnequ(i).effect(p);
    }
}
bool operate(status* p)
{
    int i,n,type;
    if(p->who)type=player.classes;
    else type=enemy.classes;
    n=p->skill;
    string name[8],explain[8];
    for(i=0; i<n; i++)
    {
        name[i]=sl[type][i].name;
        explain[i]=sl[type][i].explain;
    }
    while(1)
    {
        color(WHITE);
        gotoxy(5,29);
        i=skillchoose(p,n,name,explain);
        if(i==-1)return true;
        if(p->cd[i])
        {
            color(RED);
            showmessage("技能冷却中！");
        }
        else if(sl[type][i].spend>p->MP)
        {
            color(RED);
            showmessage("法力不足！");
        }
        else if(bulletspend[i]>p->special)
        {
            color(RED);
            showmessage("子弹不足！");
        }
        else
        {
            sl[type][i].sp(p);
            return false;
        }
    }
}
void setbuff(status* p,int type,int t,int d,double r)
{
	double sum=0;
	int maxd=d,mind=p->attribute[t].duration;
	if(type==ATT)
	{
		if(p->attribute[t].duration>d)
		{
			maxd=p->attribute[t].duration;
			mind=d;
		}
		sum=d*r+p->attribute[t].duration*p->attribute[t].ratio+mind*r*p->attribute[t].ratio;
		sum/=maxd;
		p->attribute[t].duration=maxd;
		p->attribute[t].ratio=sum;
	}
	else if(type==DEB)
	{
		if(t!=3)
		{
			if(p->debuff[t].duration>maxd)maxd=p->debuff[t].duration;
			sum=d*r+p->debuff[t].duration*p->debuff[t].ratio;
			sum/=maxd;
			p->debuff[t].duration=maxd;
			p->debuff[t].ratio=sum;
		}
		else
		{
			p->debuff[t].duration+=d;
		}
	}
}
void dealbuff(status* p)
{
    int i;
    status f;
    if(p->who)f=myrole.battlestatus(true);
    else f=enemyrole.battlestatus(false);
    for(i=0; i<8; i++)
        if(!p->attribute[i].duration)p->attribute[i].ratio=0;
    for(i=0; i<4; i++)
        if(!p->debuff[i].duration)p->debuff[i].ratio=0;
    for(i=0; i<8; i++) //攻防强抗速闪暴命
    {
        switch(i)
        {
        case 0:
            p->atk=(int)(f.atk*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 1:
            p->def=(int)(f.def*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 2:
            p->abp=(int)(f.abp*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 3:
            p->abr=(int)(f.abr*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 4:
            p->spd=(int)(f.spd*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 5:
            p->avd=(int)(f.avd*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 6:
            p->crt=(int)(f.crt*(1+p->attribute[i].ratio)+0.00001);
            break;
        case 7:
            p->hit=(int)(f.hit*(1+p->attribute[i].ratio)+0.00001);
            break;
        }
    }
    showsta(*p);
    showbuff(*p);
}
int damage(status* p,int ty,double dam,int bar)
{
    int dmg;
    string s;
    char d[10];
    //
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    //
    if(ty==AD)dmg=(int)(40*dam/(40+p->def));
    else if(ty==AP)dmg=(int)(40*dam/(40+p->abr));
    else dmg=(int)dam;
    itoa(dmg>0?dmg:(-dmg),d,10);
    if(bar==HPbar)
    {
        if(dam>0)color(GREEN);
        else if(dam<0)color(RED);
        p->HP+=dmg;
        if(p->HP>p->HPmax)p->HP=p->HPmax;
        if(p->HP<0)p->HP=0;
        if(dmg<0)showmessage(s+"受到"+d+"点伤害。");
        else if(dmg>0)showmessage(s+"恢复"+d+"点生命。");
    }
    else if(bar==MPbar)
    {
        color(BLUE);
        p->MP+=dmg;
        if(p->MP>p->MPmax)p->MP=p->MPmax;
        if(p->MP<0)p->MP=0;
        if(dmg<0)showmessage(s+"消耗"+d+"点法力。");
        else if(dmg>0)showmessage(s+"恢复"+d+"点法力。");
    }
    else
    {
        color(CYAN);
        p->move+=dam;
        p->move+=0.00000001;
        if(p->move>1)p->move=1;
        if(p->move<0)p->move=0;
        showmessage(s+percent(dam)+"行动条。");
        drawmvbar(p->move,p->who);
    }
    showbar(*p);
    return dmg;
}
void showbar(status p)
{
    if(p.who)
    {
        double per;
        per=(double)p.HP/p.HPmax;
        gotoxy(2,37);
        if(per>0.6)color(GREEN);
        else if(per<0.3)color(RED);
        else color(YELLOW);
        drawbar(per);
        per=(double)p.MP/p.MPmax;
        gotoxy(2,39);
        color(BLUE);
        drawbar(per);
        color(WHITE);
        gotoxy(27,37);
        cout<<"             ";
        gotoxy(27,37);
        cout<<p.HP<<'/'<<p.HPmax;
        gotoxy(27,38);
        cout<<'+'<<p.HPrec;
        gotoxy(27,39);
        cout<<"             ";
        gotoxy(27,39);
        cout<<p.MP<<'/'<<p.MPmax;
        gotoxy(27,40);
        cout<<'+'<<p.MPrec;
    }
    else
    {
        double per;
        per=(double)p.HP/p.HPmax;
        gotoxy(2,2);
        if(per>0.6)color(GREEN);
        else if(per<0.3)color(RED);
        else color(YELLOW);
        drawbar(per);
        per=(double)p.MP/p.MPmax;
        gotoxy(2,4);
        color(BLUE);
        drawbar(per);
        color(WHITE);
        gotoxy(27,2);
        cout<<"             ";
        gotoxy(27,2);
        cout<<p.HP<<'/'<<p.HPmax;
        gotoxy(27,3);
        cout<<'+'<<p.HPrec;
        gotoxy(27,4);
        cout<<"             ";
        gotoxy(27,4);
        cout<<p.MP<<'/'<<p.MPmax;
        gotoxy(27,5);
        cout<<'+'<<p.MPrec;
    }
}
void showsta(status p)
{
    if(p.who)
    {
        status f;
        f=myrole.battlestatus(true);
        gotoxy(47,35);
        writenum(p.atk,f.atk);
        gotoxy(58,35);
        writenum(p.def,f.def);
        gotoxy(69,35);
        writenum(p.abp,f.abp);
        gotoxy(80,35);
        writenum(p.abr,f.abr);
        gotoxy(47,36);
        writenum(p.spd,f.spd);
        gotoxy(58,36);
        writenum(p.avd,f.avd);
        gotoxy(69,36);
        writenum(p.crt,f.crt);
        gotoxy(80,36);
        writenum(p.hit,f.hit);
    }
    else
    {
        status f;
        f=enemyrole.battlestatus(false);
        gotoxy(47,0);
        writenum(p.atk,f.atk);
        gotoxy(58,0);
        writenum(p.def,f.def);
        gotoxy(69,0);
        writenum(p.abp,f.abp);
        gotoxy(80,0);
        writenum(p.abr,f.abr);
        gotoxy(47,1);
        writenum(p.spd,f.spd);
        gotoxy(58,1);
        writenum(p.avd,f.avd);
        gotoxy(69,1);
        writenum(p.crt,f.crt);
        gotoxy(80,1);
        writenum(p.hit,f.hit);
    }
}
void showbuff(status p)
{
    int i;
    color(WHITE);
    if(p.who)gotoxy(5,33);
    else gotoxy(5,7);
    cout<<"                                                                                                                     ";
    if(p.who)gotoxy(5,33);
    else gotoxy(5,7);
    for(i=0; i<8; i++)
    {
        if(p.attribute[i].duration)
        {
            if(p.attribute[i].ratio>=0)color(GREEN);
            else color(RED);
            switch(i)//攻防强抗速闪暴命
            {
            case 0:
                cout<<p.attribute[i].duration<<'x'<<"攻击"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 1:
                cout<<p.attribute[i].duration<<'x'<<"护甲"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 2:
                cout<<p.attribute[i].duration<<'x'<<"法强"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 3:
                cout<<p.attribute[i].duration<<'x'<<"魔抗"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 4:
                cout<<p.attribute[i].duration<<'x'<<"速度"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 5:
                cout<<p.attribute[i].duration<<'x'<<"闪避"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 6:
                cout<<p.attribute[i].duration<<'x'<<"暴击"<<percent(p.attribute[i].ratio)<<' ';
                break;
            case 7:
                cout<<p.attribute[i].duration<<'x'<<"命中"<<percent(p.attribute[i].ratio)<<' ';
                break;
            }
        }
    }
    for(i=0; i<4; i++) //流血燃烧中毒眩晕
    {
        color(RED);
        if(p.debuff[i].duration)
        {
            char d[5];
            itoa((int)p.debuff[i].ratio,d,10);
            switch(i)
            {
            case 0:
                cout<<p.debuff[i].duration<<'x'<<"流血-"<<d<<' ';
                break;
            case 1:
                cout<<p.debuff[i].duration<<'x'<<"燃烧-"<<d<<' ';
                break;
            case 2:
                cout<<p.debuff[i].duration<<'x'<<"中毒-"<<d<<' ';
                break;
            case 3:
                cout<<p.debuff[i].duration<<'x'<<"眩晕"<<' ';
                break;
            }
        }
    }
}
string percent(double p)
{
    char a[5];
    string s;
    if(p>=0)s="+";
    else p=-p,s="-";
    p+=0.0000001;
    itoa((int)(p*100),a,10);
    s+=a;
    s+='%';
    return s;
}
void showskill()
{
    color(WHITE);
    gotoxy(5,35);
    cout<<myrole.name<<'('<<"LV."<<player.lv<<classesname[player.classes]<<')';
    switch(player.classes)
    {
    case 0://战士
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"嗜血:攻击命中敌方时，进行一次自然生命恢复。";
        }
        if(player.lv>=10)
        {
            gotoxy(42,39);
            cout<<"猛击:攻击命中敌方时，每造成3点伤害便减少对";
            gotoxy(42,40);
            cout<<"方1%行动条。";
        }
        break;
    case 1://法师
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"嗜法:攻击命中敌方时，进行一次自然法力恢复。";
        }
        if(player.lv>=10)
        {
            gotoxy(42,39);
            cout<<"相位转移:战斗开始时和进行攻击后，增加50%的";
            gotoxy(42,40);
            cout<<"行动条。";
        }
        break;
    case 2://刺客
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"双匕:攻击命中敌方时，有50%概率造成两次伤害。";
        }
        if(player.lv>=10)
        {
            gotoxy(42,39);
            cout<<"伺机待发:回合结束时，有20%概率立刻进行一个额";
            gotoxy(42,40);
            cout<<"外的回合。";
        }
        break;
    case 3://咒术师
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"恶毒:回合结束时，使敌方随机症状持续回合+1。";
        }
        if(player.lv>=10)
        {
            gotoxy(42,39);
            cout<<"宁静结界:回合结束时恢复3%的最大生命值和最大";
            gotoxy(42,40);
            cout<<"法力值。";
        }
        break;
    case 4://神枪手
        s_showbullet(&player);
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"爆裂子弹:子弹命中敌方时，每有5点法强便额外造";
            gotoxy(42,39);
            cout<<"成其最大生命值1%的魔法伤害。";
        }
        if(player.lv>=10)
        {
            gotoxy(42,40);
            cout<<"动量射击:子弹命中敌方时，使其行动条减半。";
        }
        break;
    case 5://影武士
        if(player.lv>=4)
        {
            gotoxy(42,38);
            cout<<"斩影:攻击将额外附加100%法强的魔法伤害。";
        }
        if(player.lv>=10)
        {
        	gotoxy(42,39);
            cout<<"暗影步:回合结束时，每损失1%的生命值便提高1%";
            gotoxy(42,40);
            cout<<"的速度，持续1回合。";
        }
        break;
    }
    if(!pvp)
    {
        gotoxy(5,0);
        cout<<enemyrole.name<<'('<<"LV."<<enemy.lv<<')';
        enemyrole.sskp();
    }
    else
    {
        gotoxy(5,0);
        cout<<enemyrole.name<<'('<<"LV."<<enemy.lv<<classesname[enemy.classes]<<')';
        switch(enemy.classes)
        {
        case 0://战士
            if(enemy.lv>=4)
            {
                gotoxy(42,3);
                cout<<"嗜血:攻击命中敌方时，进行一次自然生命恢复。";
            }
            if(enemy.lv>=10)
            {
                gotoxy(42,4);
                cout<<"猛击:攻击命中敌方时，每造成3点伤害便减少对";
                gotoxy(42,5);
                cout<<"方1%行动条。";
            }
            break;
        case 1://法师
            if(enemy.lv>=4)
            {
                gotoxy(42,3);
                cout<<"嗜法:攻击命中敌方时，进行一次自然法力恢复。";
            }
            if(enemy.lv>=10)
            {
                gotoxy(42,4);
                cout<<"相位转移:战斗开始时以及进行攻击后，增加50%的";
                gotoxy(42,5);
                cout<<"行动条。";
            }
            break;
        case 2://刺客
            if(enemy.lv>=4)
            {
                gotoxy(42,3);
                cout<<"双匕:攻击命中敌方时，有50%概率造成两次伤害。";
            }
            if(enemy.lv>=10)
            {
                gotoxy(42,4);
                cout<<"伺机待发:回合结束时，有20%的概率立刻进行一个";
                gotoxy(42,5);
                cout<<"额外的回合。";
            }
            break;
        case 3://咒术师
            if(player.lv>=4)
            {
                gotoxy(42,3);
                cout<<"恶毒:回合结束时，使敌方随机症状持续回合+1。";
            }
            if(player.lv>=10)
            {
                gotoxy(42,4);
                cout<<"宁静结界:回合结束时恢复3%的最大生命值和最大";
                gotoxy(42,5);
                cout<<"法力值。";
            }
            break;
        case 4://神枪手
            s_showbullet(&enemy);
            if(player.lv>=4)
            {
                gotoxy(42,3);
                cout<<"爆裂子弹:子弹命中敌方时，每有5点法强便额外造";
                gotoxy(42,4);
                cout<<"成其最大生命值1%的魔法伤害。";
            }
            if(player.lv>=10)
            {
                gotoxy(42,5);
                cout<<"动量射击:子弹命中敌方时，使其行动条减半。";
            }
            break;
        case 5://影武士
        if(player.lv>=4)
        {
            gotoxy(42,3);
            cout<<"斩影:攻击将额外附加100%法强的魔法伤害。";
        }
        if(player.lv>=10)
        {
        	gotoxy(42,4);
            cout<<"暗影步:回合结束时，每损失1%的生命值便提高1%的";
            gotoxy(42,5);
            cout<<"速度，持续1回合。";
        }
        break;
        }
    }
}
//技能：战士
void w_bloodsuck(status* p)
{
    //嗜血
    //被动:攻击命中敌人时，进行一次自然生命恢复。
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    color(WHITE);
    showmessage(s+"触发被动嗜血，进行一次自然生命恢复。");
    damage(p,RE,p->HPrec,HPbar);
}
void w_beatback(status* p,double ham)
{
    //猛击
    //被动:攻击命中敌人时，每有3点攻击力便减少对方1%行动条。
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    color(WHITE);
    showmessage(s+"触发被动猛击，击退对方行动条。");
    damage(e,RE,0.01*ham/3,MVbar);
}
void w_0attack(status* p)
{
    //攻击
    //无消耗,命中80%,暴击20%:对敌方进行普通攻击，造成基于攻击力的物理伤害。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(w_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)ham=damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))w_bloodsuck(p);
    if(hit&&(p->lv>=10))w_beatback(p,ham);
}
void w_1charge(status* p)
{
    //冲锋
    //消耗20MP:进行冲锋，提升200%的攻击2回合并增加75%行动条。
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="进行冲锋，提升攻击并增加行动条。" ;
    damage(p,RE,-sl[0][1].spend,MPbar);
    p->cd[1]=sl[0][1].cd+1;
    PlaySound(w_1,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,0,2,2);
    if(p->attribute[4].ratio<0)p->attribute[4].duration=0;
    dealbuff(p);
    damage(p,RE,0.8,MVbar);
}
void w_2disarm(status* p)
{
    //缴械
    //消耗20MP,命中75%:破坏敌人装备，降低敌人50%的攻击与护甲5回合。
    string s;
    status *e;
    bool hit=false;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="发动缴械，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        s+="降低对方攻击与护甲。";
        hit=true;
    }
    else s+="未命中。";
    damage(p,RE,-sl[0][2].spend,MPbar);
    p->cd[2]=sl[0][2].cd+1;
    PlaySound(w_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,ATT,0,4,-0.6);
    	setbuff(e,ATT,1,4,-0.6);
        dealbuff(e);
    }
}
void w_3stone(status* p)
{
    //磐石之力
    //消耗25MP:以坚如磐石的意志强化自身，提升300%魔抗3回合并清除所有减益状态。
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="发动磐石之力，提升魔抗并清除减益状态。" ;
    damage(p,RE,-sl[0][3].spend,MPbar);
    p->cd[3]=sl[0][3].cd+1;
    PlaySound(w_3,NULL,PM);
    color(WHITE);
    showmessage(s);
    for(int i=0; i<8; i++)
        if(p->attribute[i].ratio<0)p->attribute[i].ratio=p->attribute[i].duration=0;
    for(int i=0; i<3; i++)p->debuff[i].duration=0;
    setbuff(p,ATT,1,6,2);
   	setbuff(p,ATT,3,6,2);
    dealbuff(p);
}
void w_4cripple(status* p)
{
    //致残打击
    //消耗20MP,命中80%,暴击25%:重创敌方的行动能力，造成120%攻击的伤害和减速效果同时使敌人流血。
    string s;
    status *e;
    bool hit=false;
    double ham;
    int d=4;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="发动致残打击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害、减速和流血。";
            ham=1.5*1.6*p->atk;
            d=6;
        }
        else
        {
            s+="造成物理伤害、减速和流血。";
            ham=1.6*p->atk;
        }
    }
    else s+="未命中。";
    damage(p,RE,-sl[0][4].spend,MPbar);
    p->cd[4]=sl[0][4].cd+1;
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        PlaySound(w_4,NULL,PM);
        damage(e,AD,-ham,HPbar);
        setbuff(e,ATT,4,d,-0.4);
    	setbuff(e,DEB,0,d,0.25*p->atk);
        dealbuff(e);
    }
    else
    {
        PlaySound(w_0,NULL,PM);
    }
}
void w_5shieldhit(status* p)
{
    //盾牌猛击
    //消耗30MP,命中100%,暴击50%:使用盾牌猛击敌人，对敌人造成基于护甲的物理伤害、击退和眩晕。
    string s,w;
    status *e;
    bool hit=false;
    double ham,mvb;
    if(p->who)
    {
        s=myrole.name;
        w=enemyrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        w=myrole.name;
        e=&player;
    }
    s+="发动盾牌猛击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.5))
        {
            s+="暴击，造成物理伤害和击退";
            ham=1.5*4*p->def;
            mvb=0.75;
        }
        else
        {
            s+="造成物理伤害和击退";
            ham=4*p->def;
            mvb=0.5;
        }
    }
    else s+="未命中。";
    damage(p,RE,-sl[0][5].spend,MPbar);
    p->cd[5]=sl[0][5].cd+1;
    PlaySound(w_5,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        damage(e,AD,-ham,HPbar);
        damage(e,RE,-mvb,MVbar);
        if(e->move<=0.0000001)
        {
            showmessage(w+"行动条触底，被眩晕。");
            setbuff(e,DEB,3,1,0);
            dealbuff(e);
        }
    }
}
void w_6bloodwake(status* p)
{
    //血气唤醒
    //消耗30MP:通过古老的法术唤醒血气，每损失1%的生命值便提高2%的攻击4回合，随后每有1点法强便恢复2%的已损生命值。
    string s;
    double ham;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="释放血气唤醒，提升攻击力并恢复生命值。" ;
    damage(p,RE,-sl[0][6].spend,MPbar);
    p->cd[6]=sl[0][6].cd+1;
    PlaySound(w_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,0,4,2*(1-(double)p->HP/p->HPmax));
    dealbuff(p);
    ham=(double)((p->HPmax-p->HP)*p->abp)/50;
    damage(p,RE,ham,HPbar);
}
void w_7rage(status* p)
{
    //毁灭之力
    //消耗10MP,命中75%,暴击10%:释放毁灭之力，消耗当前生命值的20%，对敌人造成该数值两倍的真实伤害，未命中时返还消耗生命值。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放雷霆毁灭，";
    damage(p,RE,-sl[0][7].spend,MPbar);
    p->cd[7]=sl[0][7].cd+1;
    ham=(int)(0.2*p->HP);
    damage(p,RE,-ham,HPbar);
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.4))
        {
            s+="暴击，造成真实伤害。";
            ham*=3;
        }
        else
        {
            s+="造成真实伤害。";
            ham*=2;
        }
    }
    else s+="未命中，返还生命值。";
    PlaySound(w_7,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,RE,-ham,HPbar);
    else damage(p,RE,ham,HPbar);
}
//技能：法师
void m_manasuck(status* p)
{
    //嗜法
    //被动:攻击命中敌人时，进行一次自然法力恢复。
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    color(WHITE);
    showmessage(s+"触发被动嗜法，进行一次自然法力恢复。");
    damage(p,RE,p->MPrec,MPbar);
}
void m_phaseblink(status* p)
{
    //相位转移
    //被动:进行攻击时，增加50%的行动条。
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    color(WHITE);
    showmessage(s+"触发被动相位转移，增加行动条。");
    damage(p,RE,0.5,MVbar);
}
void m_0attack(status* p)
{
    //攻击
    //无消耗,命中80%,暴击20%:对敌方进行普通攻击，造成基于攻击力的物理伤害。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(m_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))m_manasuck(p);
    if(p->lv>=10)m_phaseblink(p);
}
void m_1enchants(status* p)
{
    //武器附魔
    //消耗20MP:为武器附上魔法，提升相当于法强的攻击力，持续5回合
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    status f;
    if(p->who)f=myrole.battlestatus(true);
    else f=enemyrole.battlestatus(false);
    s+="为武器附魔，提升攻击力并立刻攻击。" ;
    damage(p,RE,-sl[1][1].spend,MPbar);
    p->cd[1]=sl[1][1].cd+1;
    PlaySound(m_1,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,0,3,(double)p->abp/f.atk);
    dealbuff(p);
    Sleep(1541);
    m_0attack(p);
}
void m_2stormshieldl(status* p)
{
    //风暴盾
    //消耗50MP:提升30%速度，每有1点法强提升5%护甲，持续6回合
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="释放风暴盾，提升自身护甲和速度。" ;
    damage(p,RE,-sl[1][2].spend,MPbar);
    p->cd[2]=sl[1][2].cd+1;
    PlaySound(m_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,1,5,0.01*p->abp);
    setbuff(p,ATT,4,5,0.3);
    dealbuff(p);
}
void m_3snowstorm(status* p)
{
    //暴风雪
    //消耗60MP,命中80%,暴击20%:召唤暴风雪攻击敌方，造成6次基于60%法强的魔法伤害，每次伤害独立计算命中与暴击，每次命中还会附加1回合的冰冻效果(降低40%速度和60%闪避)。
    string s;
    status *e;
    double ham=0;
    int hit=0,crt=0;
    char d[2];
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放暴风雪，";
    damage(p,RE,-sl[1][3].spend,MPbar);
    p->cd[3]=sl[1][3].cd+1;
    for(int i=1; i<=6; i++)
    {
        if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
        {
            hit++;
            if(hitthat((double)(p->crt+100)/100*0.2))
            {
                crt++;
                ham+=1.5*0.4*p->abp;
            }
            else
            {
                ham+=0.4*p->abp;
            }
        }
    }
    if(hit==0)
    {
        s+="未命中。";
        PlaySound(m_3,NULL,PM);
        color(WHITE);
        showmessage(s);
    }
    else
    {
        s+="命中";
        itoa(hit,d,10);
        s+=d;
        s+="次暴击";
        itoa(crt,d,10);
        s+=d;
        s+="次，造成魔法伤害和冰冻。";
        PlaySound(m_3,NULL,PM);
        color(WHITE);
        showmessage(s);
        damage(e,AP,-ham,HPbar);
        setbuff(e,ATT,4,hit,-0.4);
        setbuff(e,ATT,5,hit,-0.8);
        dealbuff(e);
    }
}
void m_4icelance(status* p)
{
    //冰枪术
    //消耗40MP,命中80%,暴击40%:向敌方发射冰枪，造成基于200%法强的魔法伤害，冰冻则伤害翻倍。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放冰枪，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.3))
        {
            s+="暴击，造成魔法伤害";
            ham=1.5*1.5*p->abp;
        }
        else
        {
            s+="造成魔法伤害";
            ham=1.5*p->abp;
        }
        if(e->attribute[4].ratio<0&&e->attribute[5].ratio<0)
		{
			s+="，对冰冻目标伤害翻倍。";
			ham*=2; 
		} 
    }
    else s+="未命中。";
    damage(p,RE,-sl[1][4].spend,MPbar);
    p->cd[4]=sl[1][4].cd+1;
    PlaySound(m_4,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AP,-ham,HPbar);
}
void m_5mindblast(status* p)
{
    //心灵震爆
    //消耗60MP,命中100%,暴击40%:用魔法直击敌方心灵，造成基于200%法强的真实伤害，并降低敌方30%的法强与魔抗3回合，该技能暴击时将眩晕敌方1回合
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放心灵震爆，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*2))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.5))
        {
            s+="暴击，造成真实伤害降低法强魔抗并眩晕。";
            ham=1.5*1.2*p->abp;
            setbuff(e,DEB,3,1,0);
        }
        else
        {
            s+="造成真实伤害降低法强魔抗。";
            ham=1.2*p->abp;
        }
    }
    else s+="未命中。";
    damage(p,RE,-sl[1][5].spend,MPbar);
    p->cd[5]=sl[1][5].cd+1;
    PlaySound(m_5,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        damage(e,RE,-ham,HPbar);
        setbuff(e,ATT,2,3,-0.5);
        setbuff(e,ATT,3,3,-0.5);
        dealbuff(e);
    }
}
void m_6muse(status* p)
{
    //冥想
    //消耗15MP,冷却9回合:进行一次冥想，每有2点法强便恢复1%的最大生命值同时减少所有技能1回合的冷却时间。
    string s;
    double ham;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="进行冥想，恢复生命值并减少技能冷却时间。" ;
    damage(p,RE,-sl[1][6].spend,MPbar);
    p->cd[6]=sl[1][6].cd+1;
    PlaySound(m_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    ham=(double)(p->HPmax*p->abp)/200;
    damage(p,RE,ham,HPbar);
    for(int i=0; i<8; i++)if(p->cd[i])p->cd[i]--;
}
void m_7manaburn(status* p)
{
    //法力燃烧
    //消耗30%MP,冷却2回合,命中100%,暴击10%:消耗自身法力来引燃敌方的法力，消耗敌方的等值法力并对敌方造成与消耗法力等值的魔法伤害。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放法力燃烧，";
    damage(p,RE,-sl[1][7].spend,MPbar);
    p->cd[7]=sl[1][7].cd+1;
    ham=(int)(0.2*p->MP);
    damage(p,RE,-ham,MPbar);
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成魔法伤害、法力损失和燃烧。";
            setbuff(e,DEB,1,2,ham*0.5);
            ham*=3;
        }
        else
        {
            s+="造成魔法伤害、法力损失和燃烧。";
            setbuff(e,DEB,1,2,ham*0.5);
            ham*=2;
        }
    }
    else s+="未命中。";
    PlaySound(m_7,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	damage(e,AP,-ham,HPbar);
        damage(e,RE,-ham,MPbar);
        dealbuff(e);
    }
}
//技能：刺客
void a_doubledagger(status* p)
{
    //双匕:攻击50%概率两次伤害。
    string s;
    status *e;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="触发被动双匕，";
    if(hitthat(0.5))
    {
        if(hitthat((double)(p->crt+100)/100*0.4))
        {
            s+="暴击，";
            ham=1.5*p->atk;
        }
        else
        {
            ham=p->atk;
        }
        Sleep(300);
        PlaySound(a_0,NULL,PM);
        color(WHITE);
        showmessage(s+"造成物理伤害。");
        damage(e,AD,-ham,HPbar);
    }
}
void a_preparation(status* p)
{
    //伺机待发:回合结束时，有20%的概率立刻进行一个额外的回合。
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    if(hitthat(0.2))
    {
        color(WHITE);
        showmessage(s+"触发被动伺机待发，进行额外回合。");
        damage(p,RE,1,MVbar);
    }
}
void a_0attack(status* p)
{
    //攻击
    //无消耗,命中80%,暴击20%:对敌方进行普通攻击，造成基于攻击力的物理伤害。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(a_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))a_doubledagger(p);
}
void a_1assassinate(status* p)
{
    //刺杀
    //消耗25MP,冷却2回合,命中100%,暴击40%:对敌方进行致命刺杀，造成基于160%攻击力的物理伤害，敌方每损失1%生命值都会提升该技能3%的伤害
    string s;
    status *e;
    bool hit=false;
    double ham,up;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行刺杀，";
    up=3*(1-(double)e->HP/e->HPmax);
    ham=1.6*p->atk*(1+up);
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.4))
        {
            s+="暴击，造成物理伤害，伤害";
            s+=percent(up);
            s+="。";
            ham*=1.5;
        }
        else
        {
            s+="造成物理伤害，伤害";
            s+=percent(up);
            s+="。";
        }
    }
    else s+="未命中。";
    damage(p,RE,-sl[2][1].spend,MPbar);
    p->cd[1]=sl[2][1].cd+1;
    PlaySound(a_1,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
}
void a_2blindingpowder(status* p)
{
    //致盲粉
    //消耗25MP,冷却5回合,命中100%:向敌方投掷致盲粉雾弹使敌人致盲，降低敌方75%的命中和暴击4回合
    string s;
    status *e;
    bool hit=false;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="投掷致盲粉雾弹，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        s+="降低对方命中和暴击。";
        hit=true;
    }
    else s+="未命中。";
    damage(p,RE,-sl[2][2].spend,MPbar);
    p->cd[2]=sl[2][2].cd+1;
    PlaySound(a_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,ATT,6,4,-0.5);
    	setbuff(e,ATT,7,4,-0.5);
        dealbuff(e);
    }
}
void a_3sneak(status* p)
{
    //潜行
    //进入潜行状态，提升400%的闪避、降低60%速度1回合，同时提高400%暴击2回合并清除所有症状
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="进入潜行状态，降低速度、提升闪避和暴击并清除症状。" ;
    damage(p,RE,-sl[2][3].spend,MPbar);
    p->cd[3]=sl[2][3].cd+1;
    PlaySound(a_3,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,4,1,-0.2);
    setbuff(p,ATT,5,1,3);
    setbuff(p,ATT,6,2,1);
    for(int i=0; i<3; i++)p->debuff[i].duration=0;
    dealbuff(p);
}
void a_4poisondagger(status* p)
{
    //淬毒匕首
    //消耗40MP,冷却4回合,命中80%,暴击20%:向敌方投掷一把淬毒匕首，造成相当于敌方当前生命值20%的物理伤害并附加5回合伤害为100%法强的中毒
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="投掷淬毒匕首，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.3))
        {
            s+="暴击，造成物理伤害和中毒。";
            ham=1.5*0.2*e->HP;
        }
        else
        {
            s+="造成物理伤害和中毒。";
            ham=0.2*e->HP;
        }
    }
    else s+="未命中。";
    damage(p,RE,-sl[2][4].spend,MPbar);
    p->cd[4]=sl[2][4].cd+1;
    PlaySound(a_4,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        damage(e,AD,-ham,HPbar);
        setbuff(e,DEB,2,4,e->HPmax*(5+p->abp*0.2)*0.01);
        dealbuff(e);
    }
}
void a_5stickstrike(status* p)
{
    //闷棍
    //消耗10MP,冷却8回合,命中100%,暴击20%:出其不意地猛击敌方头部，使敌人眩晕1(暴击:2)回合
    string s;
    status *e;
    bool hit=false;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="发动闷棍，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.1))
        {
            s+="暴击，降低护甲并眩晕。";
            setbuff(e,DEB,3,2,0);
        }
        else
        {
            s+="降低护甲并眩晕。";
            setbuff(e,DEB,3,1,0);
        }
    }
    else s+="未命中。";
    damage(p,RE,-sl[2][5].spend,MPbar);
    p->cd[5]=sl[2][5].cd+1;
    PlaySound(a_5,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
	{
		setbuff(e,ATT,1,3,-0.4);
		dealbuff(e);
	} 

}
void a_6weakagent(status* p)
{
    //虚弱药剂
    //消耗40MP,冷却2回合,命中100%:向敌方投掷一瓶虚弱药剂使得敌方状态虚弱3回合，虚弱状态时降低50%的攻击、法强与速度
    string s;
    status *e;
    bool hit=false;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="投掷虚弱药剂，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        s+="降低对方攻击与法强。";
        hit=true;
    }
    else s+="未命中。";
    damage(p,RE,-sl[2][6].spend,MPbar);
    p->cd[6]=sl[2][6].cd+1;
    PlaySound(a_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,ATT,0,4,-0.5);
    	setbuff(e,ATT,2,4,-0.5);
        dealbuff(e);
    }
}
void a_7fatalrhythm(status* p)
{
    //致命节奏
    //消耗30MP,冷却6回合:对敌方进行一次攻击，本回合内所有的攻击结束后都有50%概率再进行一次攻击
    string s;
    int k=3;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="发动致命节奏，进行若干次攻击。" ;
    damage(p,RE,-sl[2][7].spend,MPbar);
    p->cd[7]=sl[2][7].cd+1;
    color(WHITE);
    showmessage(s);
    a_0attack(p);
    while(k)
    {
        if(hitthat(0.5))
        {
            a_0attack(p);
            Sleep(300);
        }
        else k--;
    }
}
//
void c_vicious(status* p)
{
    //恶毒:回合结束时，使敌方症状持续回合+1。
    string s;
    status *e;
    int k,d;
    k=rand()%3;
    d=rand()%2;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    for(int i=0; i<3; i++)
    {
        if(e->debuff[k].duration)
        {
            s+="触发被动恶毒，使对方";
            switch(k)
            {
            case 0:
                s+="流血";
                break;
            case 1:
                s+="燃烧";
                break;
            case 2:
                s+="中毒";
                break;
            }
            color(WHITE);
            showmessage(s+"持续回合+1。");
            e->debuff[k].duration++;
            dealbuff(e);
            return;
        }
        else if(d)INC(k,3);
        else DEC(k,3);
    }
}
void c_boundary(status* p)
{
    //宁静结界:回合结束时恢复3%的最大生命值和最大法力值
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    color(WHITE);
    showmessage(s+"触发被动宁静结界，恢复生命和法力。");
    damage(p,RE,0.03*p->HPmax,HPbar);
    damage(p,RE,0.03*p->MPmax,MPbar);
}
void c_0attack(status* p)
{
    //攻击
    //无消耗,命中80%,暴击20%:对敌方进行普通攻击，造成基于攻击力的物理伤害。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(c_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
}
void c_1sectumsempra(status* p)
{
    //神锋咒
    //消耗30MP,冷却5回合,命中100%,暴击25%:造成4(暴击:6)回合伤害为100%攻击的流血
    string s;
    status *e;
    bool hit=false;
    int d=4;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放神锋咒，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.25))
        {
            s+="暴击，造成流血。";
            d=6;
        }
        else
        {
            s+="造成流血。";
        }
    }
    else s+="未命中。";
    damage(p,RE,-sl[3][1].spend,MPbar);
    p->cd[1]=sl[3][1].cd+1;
    PlaySound(c_1,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,DEB,0,d,p->atk);
        dealbuff(e);
    }
}
void c_2blaze(status* p)
{
    //烈火咒
    //消耗30MP,冷却5回合,命中100%,暴击25%:造成4(暴击:6)回合伤害为100%法强的燃烧
    string s;
    status *e;
    bool hit=false;
    int d=4;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放烈火咒，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.25))
        {
            s+="暴击，造成燃烧。";
            d=6;
        }
        else
        {
            s+="造成燃烧。";
        }
    }
    else s+="未命中。";
    damage(p,RE,-sl[3][2].spend,MPbar);
    p->cd[2]=sl[3][2].cd+1;
    PlaySound(c_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,DEB,1,d,p->abp);
        dealbuff(e);
    }
}
void c_3fivepoisons(status* p)
{
    //五毒咒
    //消耗40MP,冷却5回合,命中100%,暴击25%:造成4(暴击:6)回合伤害为50%攻击50%法强的中毒
    string s;
    status *e;
    bool hit=false;
    int d=4;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放五毒咒，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.25))
        {
            s+="暴击，造成中毒。";
            d=6;
        }
        else
        {
            s+="造成中毒。";
        }
    }
    else s+="未命中。";
    damage(p,RE,-sl[3][3].spend,MPbar);
    p->cd[3]=sl[3][3].cd+1;
    PlaySound(c_3,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	setbuff(e,DEB,2,d,0.5*(p->atk+p->abp));
        dealbuff(e);
    }
}
void c_4daemon(status* p)
{
    //守护咒
    //根据敌方攻击与法强的比例，自适应地提升总和相当于120%法强的护甲与魔抗，持续10回合
    string s;
    status *e;
    double k;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放守护咒，提升自身护甲、魔抗和速度。" ;
    damage(p,RE,-sl[3][4].spend,MPbar);
    p->cd[4]=sl[3][4].cd+1;
    PlaySound(c_4,NULL,PM);
    color(WHITE);
    showmessage(s);
    k=(double)e->atk/(e->atk+e->abp);
    setbuff(p,ATT,4,1,2);
    setbuff(p,ATT,1,6,0.02*p->abp*k);
    setbuff(p,ATT,3,6,0.02*p->abp*(1-k));
    dealbuff(p);
}
void c_5increase(status* p)
{
    //增幅咒
    //消耗10MP,冷却1回合,命中100%:咒语增幅敌方的所有症状，使敌方所有症状持续回合+1
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放增幅咒，使对方症状持续回合+1。";
    damage(p,RE,-sl[3][5].spend,MPbar);
    p->cd[5]=sl[3][5].cd+1;
    PlaySound(c_5,NULL,PM);
    color(WHITE);
    showmessage(s);
    for(int i=0; i<3; i++)
        if(e->debuff[i].duration)e->debuff[i].duration++;
    dealbuff(e);
}
void c_6imperio(status* p)
{
    //夺魂咒
    //无消耗,冷却10回合,命中100%:造成其最大生命法力值10%的真实伤害并为自身恢复等于该值的生命法力值
    string s;
    status *e;
    bool hit=false;
    double ham1,ham2;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放夺魂咒，";
    damage(p,RE,-sl[3][6].spend,MPbar);
    p->cd[6]=sl[3][6].cd+1;
    ham1=(int)(0.2*e->HPmax);
    ham2=(int)(0.2*e->MPmax);
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        s+="偷取生命值和法力值。";
        hit=true;
    }
    else s+="未命中。";
    PlaySound(c_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        damage(e,RE,-ham1,HPbar);
        damage(e,RE,-ham2,MPbar);
        damage(p,RE,ham1,HPbar);
        damage(p,RE,ham2,MPbar);
    }
}
void c_7summarycurse(status* p)
{
    //万咒覆灭引
    //消耗50MP,冷却5回合,命中100%:引导施加在敌方身上的所有咒语效果，清除敌方所有症状并将所有症状将产生伤害瞬间施加于敌方
    string s;
    status *e;
    double ham[3],sum=0;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放万咒覆灭引，总结所有症状伤害。";
    damage(p,RE,-sl[3][7].spend,MPbar);
    p->cd[7]=sl[3][7].cd+1;
    PlaySound(c_7,NULL,PM);
    color(WHITE);
    showmessage(s);
    for(int i=0; i<3; i++)
    {
        ham[i]=e->debuff[i].duration*e->debuff[i].ratio;
        e->debuff[i].duration=0;
    }
    dealbuff(e);
    sum+=40*ham[0]/(40+e->def);
    sum+=40*ham[1]/(40+e->abr);
    sum+=ham[2];
    damage(e,RE,-sum,HPbar);
}
//
void s_showbullet(status* p)
{
    if(p->who) gotoxy(53,37);
    else gotoxy(53,2);
    // 
    color(WHITE);
    cout<<"弹轮:";
    if(p->special)color(GREEN);
    else color(RED);
    cout<<p->special;
    color(WHITE);
    cout<<"/6";
}
void s_burstbullet(status* p)
{
    //爆裂子弹:子弹命中敌人时，每有5点法强便额外造成其最大生命值1%的魔法伤害。
    string s;
    status *e;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    ham=e->HPmax*0.01*p->abp*0.2;
    color(WHITE);
    showmessage(s+"触发被动爆裂子弹，造成魔法伤害。");
    damage(e,AP,-ham,HPbar);
}
void s_momentumshoot(status* p)
{
    //动量射击:子弹命中敌人时，使其行动条减半
    string s;
    status *e;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    ham=e->move*0.5;
    color(WHITE);
    showmessage(s+"触发被动动量射击，减半对方行动条。");
    damage(e,RE,-ham,MVbar);
}
void s_0attack(status* p)
{
    //消耗1发子弹/无消耗,无冷却,命中80%,暴击20%:向敌人发射一发子弹，造成100%攻击力的物理伤害。弹轮中无子弹时将进行填装，将弹轮填满。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    if(p->special==0)
    {
        PlaySound(s_1,NULL,PM);
        color(WHITE);
        showmessage(s+"进行填装，弹轮被填满。");
        p->special=6;
        s_showbullet(p);
        return;
    }
    s+="进行攻击，";
    p->special--;
    s_showbullet(p);
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(s_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))s_burstbullet(p);
    if(hit&&(p->lv>=10))s_momentumshoot(p);
}
void s_1quickfire(status* p)
{
    //消耗30MP+1发子弹,冷却2回合:快速拔枪对敌人进行一次攻击，随后获得一个额外回合。
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    damage(p,RE,-sl[4][1].spend,MPbar);
    p->cd[1]=sl[4][1].cd+1;
    color(WHITE);
    showmessage(s+"释放快速拔枪，攻击并进行额外回合。");
    s_0attack(p);
    damage(p,RE,1,MVbar);
}
void s_2deadeyeshoot(status* p)
{
    //消耗40MP,冷却3回合,命中100%,暴击20%:向敌方要害进行一次精准射击，造成200%攻击力的物理伤害，每有1点命中都会提升该技能1%的伤害
    string s;
    status *e;
    bool hit=false;
    double ham,up;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行精准射击，";
    up=p->hit*0.5*0.01;
    ham=1.6*p->atk*(1+up);
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害，伤害";
            s+=percent(up);
            s+="。";
            ham*=1.5;
        }
        else
        {
            s+="造成物理伤害，伤害";
            s+=percent(up);
            s+="。";
        }
    }
    else s+="未命中。";
    damage(p,RE,-sl[4][2].spend,MPbar);
    p->cd[2]=sl[4][2].cd+1;
    p->special-=bulletspend[2];
    s_showbullet(p);
    PlaySound(s_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))s_burstbullet(p);
    if(hit&&(p->lv>=10))s_momentumshoot(p);
}
void s_3tacticalcounter(status* p)
{
    //对敌方进行一次战术反制，偷取对方行动条
    string s;
	status *e;
	bool hit=false;
	double k;
    if(p->who)
	{
		s=myrole.name;
		e=&enemy;
	}
    else 
	{
		s=enemyrole.name;
		e=&player;
	}
    s+="进行战术反制，" ;
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
    	hit=true;
		s+="偷取对方行动条。";
	} 
    else s+="失败。";
    damage(p,RE,-sl[4][3].spend,MPbar);
    p->cd[3]=sl[4][3].cd+1;
    k=e->move;
    PlaySound(s_3,NULL,PM);
    color(WHITE);
	showmessage(s);
	if(hit)
	{
	    damage(e,RE,-k,MVbar);
	    damage(p,RE,k,MVbar);
	}
}
void s_4interceptingshoot(status* p)
{
    //消耗60MP,冷却6回合,命中80%,暴击20%:向敌方连续发射三发子弹，造成3次120%攻击力的物理伤害，每发子弹独立计算命中与暴击，若三发子弹全部命中则眩晕敌方1回合
    string s;
    status *e;
    double ham=0;
    int hit=0;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行拦截射击，发射三发子弹。";
    damage(p,RE,-sl[4][4].spend,MPbar);
    p->cd[4]=sl[4][4].cd+1;
    color(WHITE);
    showmessage(s);
    for(int i=1; i<=3; i++)
    {
        p->special--;
        s_showbullet(p);
        PlaySound(s_0,NULL,PM);
        if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
        {
            hit++;
            if(hitthat((double)(p->crt+100)/100*0.2))
            {
                showmessage("子弹命中，暴击。");
                ham=1.5*p->atk;
            }
            else
            {
                showmessage("子弹命中。");
                ham=p->atk;
            }
            damage(e,AD,-ham,HPbar);
            if(hit&&(p->lv>=4))s_burstbullet(p);
            if(hit&&(p->lv>=10))s_momentumshoot(p);
        }
        else showmessage("子弹未命中。");
        Sleep(500);
    }
    if(hit==3)
    {
        showmessage("子弹全部命中，造成眩晕。");
        e->debuff[3].duration=1;
        dealbuff(e);
    }
}
void s_5quickreload(status* p)
{
    //消耗50MP,冷却5回合:进行一次快速填装，将弹轮填满，随后进行一个额外回合。
    string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    damage(p,RE,-sl[4][5].spend,MPbar);
    p->cd[5]=sl[4][5].cd+1;
    PlaySound(s_1,NULL,PM);
    color(WHITE);
    showmessage(s+"进行快速填装，填装并进行额外回合。");
    p->special=6;
    s_showbullet(p);
    damage(p,RE,1,MVbar);
}
void s_6deathmarker(status* p)
{
    //对敌方施加一个死亡标记，降低其50%的护甲与魔抗2回合
    string s;
	status *e;
	bool hit=false;
    if(p->who)
	{
		s=myrole.name;
		e=&enemy;
	}
    else 
	{
		s=enemyrole.name;
		e=&player;
	}
    s+="施加死亡标记，";
    damage(p,RE,-sl[4][6].spend,MPbar);
    p->cd[6]=sl[4][6].cd+1;
    PlaySound(s_6,NULL,PM);
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
	{
		hit=true;
    	s+="降低对方护甲和魔抗。";
    }
    else s+="未命中。"; 
    color(WHITE);
	showmessage(s);
    if(hit)
    {
    	setbuff(e,ATT,1,2,-0.8);
    	setbuff(e,ATT,3,2,-0.8);
		dealbuff(e);
    }
}
void s_7stormshoot(status* p)
{
    //消耗80MP,冷却8回合,命中60%,暴击10%:快速向敌方发射出弹轮中所有的子弹，每发子弹造成150%攻击力的物理伤害，每发子弹独立计算命中与暴击。
    string s;
    status *e;
    double ham=0;
    int hit=0;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放暴雨疾射，发射所有剩余子弹。";
    damage(p,RE,-sl[4][7].spend,MPbar);
    p->cd[7]=sl[4][7].cd+1;
    color(WHITE);
    showmessage(s);
    while(p->special)
    {
        p->special--;
        s_showbullet(p);
        PlaySound(s_0,NULL,PM);
        if(hitthat((double)(p->hit+100)/(e->avd+100)*0.6))
        {
            hit++;
            if(hitthat((double)(p->crt+100)/100*0.1))
            {
                showmessage("子弹命中，暴击。");
                ham=1.5*1.5*p->atk;
            }
            else
            {
                showmessage("子弹命中。");
                ham=1.5*p->atk;
            }
            damage(e,AD,-ham,HPbar);
            s_burstbullet(p);
            s_momentumshoot(p);
        }
        else showmessage("子弹未命中。");
        Sleep(300);
    }
}
//
void d_shadowchop(status* p)
{
	//斩影:攻击将额外附加100%法强的魔法伤害。
	string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    color(WHITE);
    showmessage(s+"触发被动斩影，造成魔法伤害。");
    damage(e,AP,-p->abp,HPbar);
}
void d_shadowstep(status* p)
{
	//暗影步:回合结束时，每损失1%的生命值便提高1%的速度，持续1回合。
	string s;
	double r;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    r=(double)(p->HPmax-p->HP)/p->HPmax;
    if(r>0)
    {
    	color(WHITE);
	    showmessage(s+"触发被动暗影步，提高速度。");
	    setbuff(p,ATT,4,1,r);
	    dealbuff(p);
    }
}
void d_0attack(status* p)
{
	//无消耗,无冷却,命中80%,暴击10%:对敌方进行普通攻击，造成100%攻击力的物理伤害。
	string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.1))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(d_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
    if(hit&&(p->lv>=4))d_shadowchop(p);
}
void d_1shadowblade(status* p)
{
	//消耗50MP,冷却5回合:以暗影缠绕太刀，提高100%的攻击和命中5回合。
	string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="释放影刃，提升自身攻击和命中。" ;
    damage(p,RE,-sl[5][1].spend,MPbar);
    p->cd[1]=sl[5][1].cd+1;
    PlaySound(d_1,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,0,5,1.5);
    setbuff(p,ATT,7,5,1.5);
    dealbuff(p);
}
void d_2curseshadow(status* p)
{
	//消耗20MP,冷却4回合,命中80%:随机转移自身两个减益状态到暗影中并以暗影捕捉敌方影子，命中时将减益状态转移给敌方。
    string s;
    status *e;
    bool hit=false;
    int d=4;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放诅咒之影，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
        hit=true;
        s+="转移自身两个减益状态给敌方。";
    }
    else s+="清除自身两个减益状态。";
    damage(p,RE,-sl[5][2].spend,MPbar);
    p->cd[2]=sl[5][2].cd+1;
    PlaySound(d_2,NULL,PM);
    color(WHITE);
    showmessage(s);
    //
    int debnum=0,deblst[12];
    for(int i=0; i<8; i++)if(p->attribute[i].ratio<0)deblst[debnum++]=i;
    for(int i=0; i<4; i++)if(p->debuff[i].duration)deblst[debnum++]=i+8; 
    int index,temp;
	for(int i=0;i<debnum-1;i++)
	{
		index=rand()%(debnum-i);
		temp=deblst[index];
		deblst[index]=deblst[debnum-i-1];
		deblst[debnum-i-1]=temp;
	}
	debnum=debnum<2?debnum:2;
	for(int i=0;i<debnum;i++)
	{
		if(hit)
	    {
	    	if(deblst[i]<8)
			setbuff(e,ATT,deblst[i],p->attribute[deblst[i]].duration,p->attribute[deblst[i]].ratio);
	    	else
	    	setbuff(e,DEB,deblst[i]-8,p->debuff[deblst[i]-8].duration,p->debuff[deblst[i]-8].ratio);
	    }
	    if(deblst[i]<8)
	    p->attribute[deblst[i]].duration=0;
	    else
	    p->debuff[deblst[i]-8].duration=0;
	}
    dealbuff(p);
    dealbuff(e);
}
void d_3triplechop(status* p)
{
	//消耗30MP,冷却3回合:快速对敌方进行连续三次攻击。
	string s;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    damage(p,RE,-sl[5][3].spend,MPbar);
    p->cd[3]=sl[5][3].cd+1;
    PlaySound(d_3,NULL,PM);
    color(WHITE);
    showmessage(s+"进行三段斩，连续攻击三次。");
    d_0attack(p);
    Sleep(300);
    d_0attack(p);
    Sleep(300);
	d_0attack(p);
}
void d_4intoshadow(status* p)
{
	//消耗50%MP,冷却4回合:消耗大量法力值形成暗影笼罩自身，提高400%闪避1回合并恢复100%消耗法力值的生命值。
	string s;
    double ham;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="释放遁入暗影，恢复生命值并提高闪避。" ;
    damage(p,RE,-sl[5][4].spend,MPbar);
    p->cd[4]=sl[5][4].cd+1;
    PlaySound(d_4,NULL,PM);
    color(WHITE);
    showmessage(s);
    ham=(int)(0.5*p->MP);
    damage(p,RE,-ham,MPbar);
    damage(p,RE,2*ham,HPbar);
	setbuff(p,ATT,5,1,4);
	dealbuff(p);
}
void d_5shadowdurance(status* p)
{
	//消耗60MP,冷却4回合，命中100%:以影子缠绕敌方阻碍敌方施法，使其攻击以外的所有技能冷却计时+2。
    string s;
    status *e;
    bool hit=false;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放影缚，";
    damage(p,RE,-sl[5][5].spend,MPbar);
    p->cd[5]=sl[5][5].cd+1;
    PlaySound(d_5,NULL,PM);
    if(hitthat((double)(p->hit+100)/(e->avd+100)))
    {
    	hit=true;
		s+="使对方技能冷却计时增加。";
	}
	else s+="未命中。";
	color(WHITE);
    showmessage(s);
	if(hit)
	{
		for(int i=1;i<8;i++)e->cd[i]+=2;
	}
}
void d_6bloodsacrifice(status* p)
{
	//消耗50%HP,冷却7回合:消耗大量生命值献祭暗影强化自身，提高25%消耗生命值的护甲和魔抗以及50%消耗生命值的法强，持续7回合。
	string s;
	double ham;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    status f;
    if(p->who)f=myrole.battlestatus(true);
    else f=enemyrole.battlestatus(false);
    s+="进行暗影血祭，提升自身护甲,魔抗和法强。" ;
    damage(p,RE,-sl[5][6].spend,MPbar);
    p->cd[6]=sl[5][6].cd+1;
    ham=(int)(0.5*p->HP);
    damage(p,RE,-ham,HPbar);
    PlaySound(d_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    setbuff(p,ATT,1,7,0.4*ham/f.def);
    setbuff(p,ATT,2,7,0.6*ham/f.abp);
    setbuff(p,ATT,3,7,0.4*ham/f.abr);
    dealbuff(p);
}
void d_7shadowswordcircle(status* p)
{
	//消耗160MP,冷却5回合:召唤8把暗影之剑攻击敌方，每把影剑独立计算命中与暴击，影剑命中时造成25%法强的真实伤害并附加3回合的对应属性减益效果。
    string s;
    status *e;
    double ham=0;
    int hit=0,crt=0;
    char d[2];
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放影剑阵，";
    damage(p,RE,-sl[5][7].spend,MPbar);
    p->cd[7]=sl[5][7].cd+1;
    PlaySound(d_7,NULL,PM);
    for(int i=0; i<8; i++)
    {
        if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
        {
            hit++;
            if(hitthat((double)(p->crt+100)/100*0.1))
            {
                crt++;
                ham+=1.5*0.25*p->abp;
            }
            else
            {
                ham+=0.25*p->abp;
            }
            setbuff(e,ATT,i,4,-0.25);
        }
    }
    if(hit==0)
    {
        s+="未命中。";
        color(WHITE);
        showmessage(s);
    }
    else
    {
        s+="命中";
        itoa(hit,d,10);
        s+=d;
        s+="次暴击";
        itoa(crt,d,10);
        s+=d;
        s+="次，造成真实伤害和减益。";
        color(WHITE);
        showmessage(s);
        damage(e,RE,-ham,HPbar);
        dealbuff(e);
    }
}
//敌人技能 
void e_regenerate(status* p)
{
	string s;
    double ham;
    if(p->who)s=myrole.name;
    else s=enemyrole.name;
    s+="发动再生，恢复大量生命值。" ;
    damage(p,RE,-100,MPbar);
    p->cd[1]=1+1;
    PlaySound(c_4,NULL,PM);
    color(WHITE);
    showmessage(s);
    ham=(double)(p->HPmax-p->HP)*0.5;
    damage(p,RE,ham,HPbar);
}
void e_gaze(status* p)
{
	string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="释放石化凝视，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*2))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成真实伤害并眩晕。";
            ham=1.5*e->HPmax*0.2;
        }
        else
        {
            s+="造成真实伤害并眩晕。";
            ham=e->HPmax*0.2;
        }
    }
    else s+="未命中。";
    damage(p,RE,-120,MPbar);
    p->cd[2]=3+1;
    PlaySound(c_6,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
        damage(e,RE,-ham,HPbar);
        setbuff(e,DEB,3,1,0);
        dealbuff(e);
    }
}
//敌人设定
void e1_op(status* p)
{
    e1_attack(p);
}
void e1_attack(status* p)
{
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(w_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)damage(e,AD,-ham,HPbar);
}
void e3_op(status* p)
{
    e3_attack(p);
}
void e3_showsk()
{
    gotoxy(42,3);
    cout<<"诅咒:攻击命中敌人时，60%概率施加1回合伤害为";
    gotoxy(42,4);
    cout<<"100%法强的流血、燃烧或中毒";
}
void e3_attack(status* p)
{
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(w_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)
    {
        damage(e,AD,-ham,HPbar);
        e3_sk(p);
    }
}
void e3_sk(status* p)
{
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    if(hitthat(0.6))
    {
        int k;
        k=rand()%3;
        s+="触发被动诅咒，造成";
        if(k==0)s+="流血。";
        else if(k==1)s+="燃烧。";
        else s+="中毒。";
        color(WHITE);
        showmessage(s);
        setbuff(e,DEB,k,1,p->abp);
        showbuff(*e);
    }
}
void e4_op(status* p)
{
    if(p->MP>=sl[0][1].spend&&p->cd[1]==0)w_1charge(p);
    else e4_attack(p);
}
void e4_showsk()
{
    color(WHITE);
    gotoxy(42,3);
    cout<<"嗜血:攻击命中敌人时，进行一次自然生命恢复。";
}
void e4_attack(status* p)
{
    //攻击
    //无消耗,命中80%,暴击20%:对敌方进行普通攻击，造成基于攻击力的物理伤害。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(w_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
	{
		damage(e,AD,-ham,HPbar);
		w_bloodsuck(p);
	}
}
void e5_op(status* p)
{
    status* e=&player;
    if(p->MP>=sl[2][7].spend&&p->cd[7]==0)m_7manaburn(p);
    else if(p->MP>=sl[3][2].spend&&p->cd[2]==0&&e->debuff[1].duration==0)c_2blaze(p);
    else e5_attack(p);
}
void e5_showsk()
{
    color(WHITE);
    gotoxy(42,3);
    cout<<"嗜法:攻击命中敌人时，进行一次自然法力恢复。";
}
void e5_attack(status* p)
{
    //攻击
    //无消耗,命中80%,暴击20%:对敌方进行普通攻击，造成基于攻击力的物理伤害。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(m_0,NULL,PM);
    color(WHITE);
    showmessage(s);
    if(hit)
    {
    	damage(e,AD,-ham,HPbar);
		m_manasuck(p);
    }
}
void e6_op(status* p)
{
    if(p->MP>=sl[2][3].spend&&p->cd[3]==0)a_3sneak(p);
    else e1_attack(p);
}
void e7_op(status* p)
{
    if(p->MP>=sl[2][5].spend&&p->cd[5]==0)m_5mindblast(p);
    else if(p->MP>=sl[3][3].spend&&p->cd[3]==0)c_3fivepoisons(p);
    else if(p->MP>=sl[3][6].spend&&p->cd[6]==0)c_6imperio(p);
    else e1_attack(p);
}
void e8_showsk()
{
    gotoxy(42,3);
    cout<<"猛击:攻击命中敌人时，每造成3点伤害便减少对";
    gotoxy(42,4);
    cout<<"方1%行动条。";
}
void e8_op(status* p)
{
    if(p->MP>=sl[0][1].spend&&p->cd[1]==0)w_1charge(p);
    else if(p->MP>=sl[0][4].spend&&p->cd[4]==0)w_4cripple(p);
    else e8_attack(p);
}
void e8_attack(status* p)
{
    //攻击
    //无消耗,命中80%,暴击20%:对敌方进行普通攻击，造成基于攻击力的物理伤害。
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(w_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)w_beatback(p,damage(e,AD,-ham,HPbar));
}
void e9_showsk()
{
    gotoxy(42,3);
    cout<<"双匕:攻击命中敌人时，有50%概率造成两次伤害。";
}
void e9_op(status* p)
{
    if(p->MP>=sl[2][3].spend&&p->cd[3]==0)a_3sneak(p);
    else if(p->MP>=sl[2][1].spend&&p->cd[1]==0)a_1assassinate(p);
    else a_0attack(p);
}
void e10_showsk()
{
    gotoxy(42,3);
    cout<<"吸血:攻击造成伤害时，恢复伤害值20%的生命。";
}
void e10_op(status* p)
{
    if(p->MP>=sl[0][6].spend&&p->cd[6]==0&&p->HP<=p->HPmax*0.3)w_6bloodwake(p);
    else if(p->MP>=sl[0][4].spend&&p->cd[4]==0)w_4cripple(p);
    else if(p->MP>=sl[2][1].spend&&p->cd[1]==0)a_1assassinate(p);
    else e10_attack(p);
}
void e10_sk(status* p,double ham)
{
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="触发被动吸血，恢复生命值。";
    color(WHITE);
    showmessage(s);
    damage(p,RE,-0.2*ham,HPbar);
}
void e10_attack(status* p)
{
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(a_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)
    {
        e10_sk(p,damage(e,AD,-ham,HPbar));
    }
}
void e11_showsk()
{
    gotoxy(42,3);
    cout<<"重击:攻击命中时，25%概率造成1回合眩晕。";
}
void e11_sk(status* p)
{
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    if(hitthat(0.25))
    {
        s+="触发被动重击，造成眩晕。";
        color(WHITE);
        showmessage(s);
        setbuff(e,DEB,3,1,0);
        showbuff(*e);
    }
}
void e11_op(status* p)
{
    if(p->MP>=sl[0][3].spend&&p->cd[3]==0&&(p->attribute[1].duration||p->attribute[3].duration||p->attribute[4].duration||p->debuff[0].duration||p->debuff[1].duration||p->debuff[2].duration))w_3stone(p);
	else if(p->MP>=sl[0][2].spend&&p->cd[2]==0)w_2disarm(p);
    else if(p->MP>=sl[0][5].spend&&p->cd[5]==0)w_5shieldhit(p);
    else e11_attack(p);
}
void e11_attack(status* p)
{
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(w_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)
    {
        damage(e,AD,-ham,HPbar);
        e11_sk(p);
    }
}
void e12_showsk()
{
    gotoxy(42,3);
    cout<<"毒牙:攻击命中敌人时，造成10回合伤害为10%法";
    gotoxy(42,4);
    cout<<"强的中毒。";
}
void e12_sk(status* p)
{
    string s;
    status *e;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="触发被动毒牙，造成中毒。";
    color(WHITE);
    showmessage(s);
    setbuff(e,DEB,2,10,p->abp*0.1);
    showbuff(*e);
}
void e12_op(status* p)
{
    if(p->HP<=p->HPmax*0.4&&p->MP>=100&&p->cd[1]==0)e_regenerate(p);
	else if(p->MP>=120&&p->cd[2]==0)e_gaze(p);
    else e12_attack(p);
}
void e12_attack(status* p)
{
    string s;
    status *e;
    bool hit=false;
    double ham;
    if(p->who)
    {
        s=myrole.name;
        e=&enemy;
    }
    else
    {
        s=enemyrole.name;
        e=&player;
    }
    s+="进行攻击，";
    if(hitthat((double)(p->hit+100)/(e->avd+100)*0.8))
    {
        hit=true;
        if(hitthat((double)(p->crt+100)/100*0.2))
        {
            s+="暴击，造成物理伤害。";
            ham=1.5*p->atk;
        }
        else
        {
            s+="造成物理伤害。";
            ham=p->atk;
        }
    }
    else s+="未命中。";
    PlaySound(c_0,NULL,PM);
    color(WHITE);showmessage(s);
    if(hit)
    {
        damage(e,AD,-ham,HPbar);
        e12_sk(p);
    }
}
