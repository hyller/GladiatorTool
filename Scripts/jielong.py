# 从接龙中提取电话号码，物品数量，方便统计总数
# 物品表述应该为：物品x单位。比如：西瓜2个。鸡蛋2个。
import sys
import re

tinydict = {'一': 1, '二': 2, '三': '3', '四': '4', '五': '5', '六': '6', '七': '7', '八': '8', '九': '9', '两': '2'}

pattern_phone = '1[3456789]\d{9}'

def extract_phone_food(filename, food, unit):
    pattern_food = food+'.'+unit
    with open(filename+'.csv', 'w+') as wf:
        with open(filename, 'r', encoding='utf-8') as rf:
            lines = rf.readlines()

            for line in lines:
                phone = re.findall(pattern_phone, line)
                if len(phone) == 0:
                    phone_num = "xxxxxxxxxxx"
                else:
                    phone_num = phone[0]
                food = re.findall(pattern_food, line)
                if len(food) == 0:
                    food_num = "0"
                else:
                    food_num = food[0]
                    food_num = food_num[2]
                    if food_num in tinydict:
                        food_num = tinydict[food_num]

                print(str(phone_num) + " | " + str(food_num) + " | " + line)
                wf.write(str(phone_num) + " | " + str(food_num) + " | " + line)

            rf.close()
        wf.close()


if __name__ == '__main__':
    if len(sys.argv) >= 4:
        extract_phone_food(sys.argv[1], sys.argv[2], sys.argv[3])
    else:
        print('usage: jielong file food unit')
        print('example: jielong xigua.txt 西瓜 个')


