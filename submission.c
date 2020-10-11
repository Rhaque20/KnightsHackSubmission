#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

/* * Status IDs
 *  1 = ATK Down, 2 = DEF Down, 3 = EFF Res down, 4 = SPD down, 5 = Burn, 6 = Stun, 7 = Paralyze, 8 = Marked
 *  9 = Fear
 * */
typedef struct fighter
{
    char *name;
    float *stats;// [0] HP, [1] ATK, [2] DEF, [3] CRIT, [4]CRIT DMG, [5]EFF, [6]EFF Res, [7] SPD, [8] Dual Strike
    float maxHP;
    float CR;
    float CRgain;
    float **status;// [0] ID [1] Stack/Power [2] Duration
    float **skills;// [0] Type [1] Skill Mod [2] Max Cooldown [3] Current Cooldown || Type 0: Passive Type 1: Attack Type 2: Skill
    float *statboost;// [0] HP, [1] ATK, [2] DEF, [3] CRIT, [4]CRIT DMG, [5]EFF, [6]EFF Res, [7] SPD, [8] Dual Strike
    int fear;

}fighter;

float *skillsetup(float *skill, float type,float mod, float cooldown)
{
    
    skill[0] = type;
    skill[1] = mod;
    skill[2] = cooldown;
    skill[3] = 0;
    
    return skill;

}

float *statsetup(float *stat,float HP, float ATK, float DEF, float CRIT, float CRITDMG, float EFF, float EFFRes,float SPD, float DS)
{
    stat[0] = HP;
    stat[1] = ATK;
    stat[2] = DEF;
    stat[3] = CRIT;
    stat[4] = CRITDMG;
    stat[5] = EFF;
    stat[6] = EFFRes;
    stat[7] = SPD;
    stat[8] = DS;

    return stat;
}

void printdebuff(float **debuff)
{
    int i;

    printf("Debuff: ");
    for(i = 0; i < 8; i++)
    {
        if(debuff[i][0] == 1)
        {
            printf("ATK DOWN (%.2f)(%.0f) ",debuff[i][1],debuff[i][2]);
        }
        if(debuff[i][0] == 2)
            printf("FEAR(%.0f) ",debuff[i][2]);
    }

    printf("\n");
}

fighter applydebuff(fighter entity, int id)
{
    int i;
    switch(id)
    {
        case 1:
        printf("%s has been afflicted with ATK Down!\n",entity.name);
        for(i = 0; i < 8; i++)
        {
            if(entity.status[i][0] == 0 || entity.status[i][0] == id)
            {
                entity.status[i][0] = id;
                entity.status[i][1] += -0.25;
                entity.status[i][2] = 3;
                entity.statboost[1] += -0.25;
                break;
            }
        }
        break;
        case 2:
        printf("%s has been afflicted with Fear!\n",entity.name);
        for(i = 0; i < 8; i++)
        {
            if(entity.status[i][0] == 0 || entity.status[i][0] == id)
            {
                entity.status[i][0] = id;
                entity.status[i][1] += 70;
                entity.status[i][2] = 3;
                break;
            }
        }
    }

    return entity;
}

fighter createentity(fighter entity, int id)
{
    int len,i;
    entity.stats = malloc(sizeof(float) * 9);
    entity.status = malloc(sizeof(float) * 8);
    entity.skills = malloc(sizeof(float) * 3);
    entity.statboost = calloc(9,sizeof(float));
    entity.fear = 0;
    entity.CR = 0;

    for(i = 0; i < 3; i++)
    {
        entity.skills[i] = malloc(sizeof(float) * 4);
    }

    for(i = 0; i < 8; i++)
    {
        entity.status[i] = calloc(3, sizeof(float));
    }

    switch(id)
    {
        case 0:
            len = strlen("Chris");
            entity.name = malloc((sizeof(char) * len) + 1);
            strcpy(entity.name,"Chris");
            entity.stats = statsetup(entity.stats,4500,850,350,5,2,5,3,85,55);
            entity.maxHP = entity.stats[0];
            entity.CRgain = entity.stats[7]/10;

            entity.skills[0] = skillsetup(entity.skills[0],1,1,0);
            entity.skills[1] = skillsetup(entity.skills[1],2,0.5,4);
            entity.skills[2] = skillsetup(entity.skills[2],2,0.6,8);
            break;
        
        
        case 4:
            len = strlen("Tree Ninja");
            entity.name = malloc((sizeof(char) * len) + 1);
            strcpy(entity.name,"Tree Ninja");
            entity.stats = statsetup(entity.stats,7500,600,100,8,2,5,3,65,5);
            entity.maxHP = entity.stats[0];
            entity.CRgain = entity.stats[7]/10;

            entity.skills[0] = skillsetup(entity.skills[0],1,1,0);
            entity.skills[1] = skillsetup(entity.skills[1],2,1.13,3);
            entity.skills[2] = skillsetup(entity.skills[2],2,0,8);
            entity.skills[2][3] = 8;

            break;

        case 5:
            len = strlen("Man-Eater");
            entity.name = malloc((sizeof(char) * len) + 1);
            strcpy(entity.name,"Man-Eater");
            entity.stats = statsetup(entity.stats,8000,800,100,5,2,5,3,55,5);
            entity.maxHP = entity.stats[0];
            entity.CRgain = entity.stats[7]/10;

            entity.skills[0] = skillsetup(entity.skills[0],1,1,0);
            entity.skills[1] = skillsetup(entity.skills[1],2,1.5,1);
            entity.skills[2] = skillsetup(entity.skills[2],1,10,10);
            entity.skills[2][3] = 10;

            break;
        
        case 6:
            len = strlen("Wyrm");
            entity.name = malloc((sizeof(char) * len) + 1);
            strcpy(entity.name,"Wyrm");
            entity.stats = statsetup(entity.stats,7600,600,100,5,2,5,3,55,15);
            entity.maxHP = entity.stats[0];
            entity.CRgain = entity.stats[7]/10;

            entity.skills[0] = skillsetup(entity.skills[0],1,1,0);
            entity.skills[1] = skillsetup(entity.skills[2],1,1,0);
            entity.skills[2] = skillsetup(entity.skills[2],1,1,0);
            
            break;
        
        case 7:
            len = strlen("Flame Naga");
            entity.name = malloc((sizeof(char) * len) + 1);
            strcpy(entity.name,"Flame Naga");
            entity.stats = statsetup(entity.stats,15000,600,100,5,2,5,3,77,0);
            entity.maxHP = entity.stats[0];
            entity.CRgain = entity.stats[7]/10;

            entity.skills[0] = skillsetup(entity.skills[0],1,1,0);
            entity.skills[1] = skillsetup(entity.skills[1],2,1.25,3);
            entity.skills[2] = skillsetup(entity.skills[2],1,2,8);
            entity.skills[2][3] = 8;
            
            break;
        
    }

    return entity;

}

float damagecalc(fighter attacker,fighter defender,float mod)
{
    float damage,range,critical,critrate;
    
    critrate = attacker.stats[3] * (1 + attacker.statboost[3]);
    range = rand()%(110 - 80 + 1) + 80;
    critical = rand()%100 + 1;
    damage = attacker.stats[1] * (1 + attacker.statboost[1]);
    damage -= defender.stats[2] * (1 + defender.statboost[2]);
    damage *= range/100 * mod;

    if(damage <= 0)
    {
        damage = 1;
    }

    if(critical <= critrate)
    {
        printf(">CRITICAL!<: ");
        damage *= attacker.stats[4];
    }

    printf("%s dealt %.0f damage to %s\n",attacker.name,damage,defender.name);
    
    return damage;
}

void battle(fighter party,fighter *horde)
{
    int choice = 0,choice2 = 0,i,j,ai,flag = 0,ko = 0,strike = -2,s = 37;
    float chance;

    while(choice != 4)
    {
        for(i = 0; i < 4; i++)
        {
            if(horde[i].stats[0] <= 0)
            {
                ko++;
            }
        }

        if(ko == 4)
        {
            printf("All enemies have been slain.\n");
            break;
        }

        if(party.stats[0] <= 0)
        {
            printf("%s has been slain. You lose.\n",party.name);
            break;
        }

        party.CR += party.CRgain;

        for(i = 0; i < 4; i++)
        {
            horde[i].CR += horde[i].CRgain;

            if(horde[i].stats[0] < 0)
            {
                horde[i].stats[0] = 0;
                horde[i].CR = 0;
            }

            if(horde[i].CR >= 100)
            {
                strike = i;
            }
        }

        if(party.CR >= 100)
        {
            for(i = 0; i < 4; i++)
            {
                if(party.CR > horde[i].CR)
                    strike = -1;
                
                if(horde[i].CR > party.CR)
                    strike = i;
            }
        }



        if(party.CR > 0 && strike == -1)
        {
            for(i = 0; i < 3; i++)
            {
                if(party.skills[i][3] != 0)
                    party.skills[i][3]--;
            }

            for(i = 0; i < 8; i++)
            {
                party.status[i][2]--;
                if(party.status[i][2] == 0)
                {
                    printf("Chris is no longer afflicted.\n");
                    for(j = 0; j < 3; j++)
                    {
                        party.status[i][j] = 0;
                    }
                }
            }

            printf("============================\n");
            printf("%s HP: %.0f/%.0f | CR: %.0f / 100\n",party.name,party.stats[0],party.maxHP,party.CR);
            printdebuff(party.status);
            printf("----------------------------\n");
            for(i = 0; i < 4; i++)
            {
                printf("%s HP: %.0f/%.0f | CR: %.0f / 100\n",horde[i].name,horde[i].stats[0],horde[i].maxHP,horde[i].CR);
                printdebuff(horde[i].status);
                if(i < 3)
                    printf("----------------------------\n");
            }
            printf("============================\n");

            printf("+-----------------------------------------------------------------+\n");
            printf("What will %s do?\n",party.name);
            printf("1) |Cleave|\n");
            printf("Does a sword strike with a chance to inflict Fear for 1 turn\n");
            printf("\n");
            printf("2) |Tranquil State CD: %.0f|\n",party.skills[1][3]);
            printf("Restore 15%c of your HP and remove 1 debuff.\n",s);
            printf("\n");
            printf("3)|Brink of Insanity CD: %.0f|\n",party.skills[2][3]);
            printf("Area of Effect attack 5 hit attack that increases in damage if target has Fear.\n");
            printf("4) Run.\n");
            printf("+-----------------------------------------------------------------+\n");
            printf("\n");
            scanf("%d",&choice);

            if(choice == 4)
                break;

            if(choice > 4 || choice < 1)
            {
                while(choice < 1 || choice > 4)
                {
                    printf("Invalid choice. Try again\n");
                    scanf("%d",&choice);
                }
            }

            if(party.skills[choice - 1][3] != 0)
            {
                printf("Chris uses Cleave!\n");

                printf("Who is your target?\n");
                for(i = 0; i < 4; i++)
                {
                    printf("%d) %s\n",i+1,horde[i].name);
                }

                scanf("%d",&choice2);

                if(choice2 > 4 || choice2 < 1)
                {
                    while(choice2 < 1 || choice2 > 4)
                    {
                        printf("Invalid choice. Try again\n");
                        scanf("%d",&choice2);
                    }
                }
                horde[choice2 - 1].stats[0] -= damagecalc(party,horde[choice2 - 1],party.skills[0][1]);
                flag = 1;
            }

            if(flag == 0)
            {
                switch(choice)
                {
                    case 1:
                        printf("Who is your target?\n");
                        for(i = 0; i < 4; i++)
                        {
                            printf("%d) %s\n",i+1,horde[i].name);
                        }

                        scanf("%d",&choice2);

                        if(choice2 > 4 || choice2 < 1)
                        {
                            while(choice2 < 1 || choice2 > 4)
                            {
                                printf("Invalid choice. Try again\n");
                                scanf("%d",&choice2);
                            }
                        }
                        printf("Chris uses Cleave!\n");
                        chance = rand()%100 + 1;
                        if(chance <= party.stats[8])
                        {
                            printf("Chris attacks twice!\n");
                            horde[choice2 - 1].stats[0] -= damagecalc(party,horde[choice2 - 1],party.skills[0][1]);
                            chance = rand()%100 + 1;
                            if(chance <= (30 + party.stats[5] - horde[choice2 - 1].stats[6]))
                            {
                                horde[choice2 - 1] = applydebuff(horde[choice2 - 1],2);
                            }
                        }
                        chance = rand()%100 + 1;
                        horde[choice2 - 1].stats[0] -= damagecalc(party,horde[choice2 - 1],party.skills[0][1]);
                        if(chance <= (50 + party.stats[5] - horde[choice2 - 1].stats[6]))
                        {
                            horde[choice2 - 1] = applydebuff(horde[choice2 - 1],2);
                        }
                        
                        break;

                    case 2:
                        printf("Chris restored %.0f HP.\n",0.5 * party.maxHP);
                        party.stats[0] += 0.5 * party.maxHP;
                        party.skills[1][3] = party.skills[1][2];

                        if(party.stats[0] > party.maxHP)
                            party.stats[0] = party.maxHP;
                        break;

                    case 3:
                        printf("Chris uses Brink of Insanity!\n");
                        for(i = 0; i < 4; i++)
                        {
                            horde[i].stats[0] -= 8 * (damagecalc(party,horde[i],party.skills[choice - 1][1]));
                        }
                        party.skills[choice - 1][3] = party.skills[choice - 1][2];
                        break;

                }
            }
            if(flag == 1)
            {
                flag = 0;
            }
            party.CR -= 100;
            printf("\n");
        }
        
        if(horde[strike].CR > 0 && strike != -1)
        {
            chance = rand()%100 + 1;

            for(i = 0; i < 8; i++)
            {
                if(horde[strike].status[i][0] == 2)
                {
                    printf("%s is too afraid to attack!\n",horde[strike].name);
                    horde[strike].fear = 1;
                    for(j = 0; j < 3; j++)
                        horde[strike].status[i][j] = 0;
                    break; 
                }
            }

            if(horde[strike].fear == 0)
            {
                for(i = 0; i < 3; i++)
                {
                    if(horde[strike].skills[i][3] != 0)
                        horde[strike].skills[i][3]--;
                }
                ai = rand()%(3)+1;
                switch(ai)
                {
                    case 1:
                        printf("%s uses Slash\n",horde[strike].name);
                        party.stats[0] -= damagecalc(horde[strike],party,horde[strike].skills[0][1]);
                        break;
                    default:
                        if(horde[strike].skills[ai - 1][3] == 0)
                        {
                            chance = rand()%100 + 1;
                            if(chance <= 5)
                            {
                                party = applydebuff(party,1);
                            }
                            printf("%s uses Swarm.\n",horde[strike].name);
                            party.stats[0] -= damagecalc(horde[strike],party,horde[strike].skills[ai - 1][1]);
                            horde[strike].skills[ai - 1][3] = horde[strike].skills[ai - 1][2];
                            
                            break;   
                        }
                        party.stats[0] -= damagecalc(horde[strike],party,horde[strike].skills[0][1]);
                        break;
                }
            }
            
            horde[strike].fear = 0;
            horde[strike].CR -= 100;
            if(horde[strike].CR < 0)
                horde[strike].CR = 0;

            strike = -1;
            printf("\n");
        }
    }

    printf("Battle cleared.\n");
}

fighter freeentity(fighter entity)
{
    int i;

    free(entity.name);
    free(entity.stats);
    free(entity.statboost);

    for(i = 0; i < 3; i++)
    {
        free(entity.skills[i]);
    }

    free(entity.skills);

    for(i = 0; i < 8; i++)
    {
        free(entity.status[i]);
    }

    free(entity.status);

    return entity;
}

int main(void)
{
    int i,rand = 4;
    fighter *party;
    fighter *monster;

    srand(time(0));

    party = malloc(sizeof(fighter) * 4);

    if(party == NULL)
    {
        printf("Too much space has been taken.\n");
        return 0;
    }

    monster = malloc(sizeof(fighter) * 4);

    if(monster == NULL)
    {
        printf("Too much space has been taken.\n");
        free(party);
        return 0;
    }

    party[0] = createentity(party[0],0);
    printf("Created %s\n",party[0].name);
    for(i = 0; i < 4; i++)
    {
        monster[i] = createentity(monster[i],rand);
        printf("Created %s\n",monster[i].name);
        rand++;
    }

    battle(party[0],monster);

    party[0] = freeentity(party[0]);
    monster[0] = freeentity(monster[0]);

    free(party);
    free(monster);
    printf("All clean ^_^.\n");
    return 0;
}