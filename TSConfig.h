#pragma once

#define  __��������ģʽ__			FALSE     //���� VMP ����, ��׮. ���Լ�� ��

#define  __����ͼɫģʽ__			FALSE     //�Ƿ�����Į�ĵ��Թ���



//ע��: ��ע��Կ���Ŀ����

#define CMD������ʼ�˿ں�           15400				//�ű��˵� ͨѶ�˿ں�
#define NET������ʼ�˿ں�           15500				//��������, ���շ�����ݵĶ˿ں�


#define  ����_�ű���������������   0x6A0F2E0F    
#define  ����_������̨����������   0x7A0F21A1    
#define  ����_�һ��ű�����������   0x5A1F0E0F  





//��¼ ��ǰ��������   ��ֹ�ⲿ���µ�, ������� ��ô�����޷�������ȡ��·������Ϣ
#define ģ��_����̨������                "ConsoleModel.exe"  

#define ģ��_������������              "CodesAnswer.exe"  

#define ģ��_�ػ�����������              "in.dll"

#define ģ��_�ػ�����������              "TSDebugModel.exe"

#define ģ��_STeam��Ϸ������             "ProjectLH.exe"  


//Ŀ¼ | �ű�Ŀ¼ 
#define STR_SCRIPTCATALOG              "script\\"   
//Ŀ¼ | ������Ŀ¼ 
#define STR_DEPLOYCATALOG              "config\\"   
//Ŀ¼ | ��Դ �ļ�
#define STR_RESOURCEFILECATALOG        "resource\\"  
//Ŀ¼ | ������־
#define STR_LOGCATALOG                 "log\\"  
//Ŀ¼ | ��֤�� ����Ŀ¼
#define STR_CODECATALOG                "verifycode\\" 
//Ŀ¼ | �������� ����Ŀ¼
#define STR_SCRIPTTMPCATALOG           "VMClient\\" 
//Ŀ¼ | �������� ����Ŀ¼
#define STR_TSCATALOG                  "ts\\" 
//Ŀ¼ | ��λ����Ŀ¼
#define STR_SEATCATALOG                "seat\\"  
//Ŀ¼ | ��չ���Ŀ¼
#define STR_PLUGINCATALOG              "plugin\\"  



//ui   ���� �ļ���
#define STR_UIDEPLOYFILENAME           "UIConfig.ini" 
//��������   ���� �ļ��� (�������ÿ���̨,��Ϸ�˵�ȫ������)
#define STR_PROPERTCONFIGFILENAME      "PropertConfig.ini" 

// �½�ɫ������ {ǰ׺}
#define STR_NEWNAMEFILEHEAD           "NameHead.txt" 
// �½�ɫ������ {��׺}
#define STR_NEWNAMEFILECENTER         "NameCenter.txt" 
// �½�ɫ������ {��׺}
#define STR_NEWNAMEFILELAST           "NameLast.txt" 


//���õ� ��־�ļ�, ȫ����־��ϢΪ�쳣��־
#define STR_MAINLOGFILENAME           "MainLog.log" 


#define key_Script                      "ִ�нű�"
#define key_EConfig                     "��չ����"
#define key_RStatus                     "��ǰ״̬"
#define key_DebugLOG                    "�����¼"
#define key_Enable					    "����״̬"

#pragma region//---------------------------------------------------------------------------------------------Ĭ����ɫֵ �ĺ궨��, �����˴󲿷ֳ�����ɫ��


#define CLR_LIGHTPINK               RGB(255, 182, 193)      // ǳ�ۺ�  
#define CLR_PINK                    RGB(255, 192, 203)      // �ۺ�  
#define CLR_CRIMSON                 RGB(220,  20,  60)      // �ɺ� (���)  
#define CLR_LAVENDERBLUSH           RGB(255, 240, 245)      // ���Ϻ�  
#define CLR_PALEVIOLETRED           RGB(219, 112, 147)      // ����������  
#define CLR_HOTPINK                 RGB(255, 105, 180)      // ����ķۺ�  
#define CLR_DEEPPINK                RGB(255,  20, 147)      // ��ۺ�  
#define CLR_MEDIUMVIOLETRED         RGB(199,  21, 133)      // ����������  
#define CLR_ORCHID                  RGB(218, 112, 214)      // ������  
#define CLR_THISTLE                 RGB(216, 191, 216)      // ��  
#define CLR_PLUM                    RGB(221, 160, 221)      // ������  
#define CLR_VIOLET                  RGB(238, 130, 238)      // ������  
#define CLR_MAGENTA                 RGB(255,   0, 255)      // ��� (Ʒ�� õ���)  
#define CLR_FUCHSIA                 RGB(255,   0, 255)      // ��������(�Ϻ�ɫ)  
#define CLR_DARKMAGENTA             RGB(139,   0, 139)      // �����  
#define CLR_PURPLE                  RGB(128,   0, 128)      // ��ɫ  
#define CLR_MEDIUMORCHID            RGB(186,  85, 211)      // ��������  
#define CLR_DARKVIOLET              RGB(148,   0, 211)      // ��������  
#define CLR_DARKORCHID              RGB(153,  50, 204)      // ��������  
#define CLR_INDIGO                  RGB( 75,   0, 130)      // ���� (����ɫ)  
#define CLR_BLUEVIOLET              RGB(138,  43, 226)      // ��������  
#define CLR_MEDIUMPURPLE            RGB(147, 112, 219)      // ����ɫ  
#define CLR_MEDIUMSLATEBLUE         RGB(123, 104, 238)      // �а�����  
#define CLR_SLATEBLUE               RGB(106,  90, 205)      // ������  
#define CLR_DARKSLATEBLUE           RGB( 72,  61, 139)      // ��������  
#define CLR_LAVENDER                RGB(230, 230, 250)      // Ѭ�²ݵ���  
#define CLR_GHOSTWHITE              RGB(248, 248, 255)      // �����  
#define CLR_BLUE                    RGB(  0,   0, 255)      // ����  
#define CLR_MEDIUMBLUE              RGB(  0,   0, 205)      // ����ɫ  
#define CLR_MIDNIGHTBLUE            RGB( 25,  25, 112)      // ��ҹ��  
#define CLR_DARKBLUE                RGB(  0,   0, 139)      // ����ɫ  
#define CLR_NAVY                    RGB(  0,   0, 128)      // ������  
#define CLR_ROYALBLUE               RGB( 65, 105, 225)      // �ʼ��� (����)  
#define CLR_CORNFLOWERBLUE          RGB(100, 149, 237)      // ʸ������  
#define CLR_LIGHTSTEELBLUE          RGB(176, 196, 222)      // ������  
#define CLR_LIGHTSLATEGRAY          RGB(119, 136, 153)      // ��ʯ���  
#define CLR_SLATEGRAY               RGB(112, 128, 144)      // ʯ���  
#define CLR_DODGERBLUE              RGB( 30, 144, 255)      // ������  
#define CLR_ALICEBLUE               RGB(240, 248, 255)      // ����˿��  
#define CLR_STEELBLUE               RGB( 70, 130, 180)      // ���� (����)  
#define CLR_LIGHTSKYBLUE            RGB(135, 206, 250)      // ������ɫ  
#define CLR_SKYBLUE                 RGB(135, 206, 235)      // ����ɫ  
#define CLR_DEEPSKYBLUE             RGB(  0, 191, 255)      // ������  
#define CLR_LIGHTBLUE               RGB(173, 216, 230)      // ����  
#define CLR_POWDERBLUE              RGB(176, 224, 230)      // ��ҩ��  
#define CLR_CADETBLUE               RGB( 95, 158, 160)      // ������  
#define CLR_AZURE                   RGB(240, 255, 255)      // ε��ɫ  
#define CLR_LIGHTCYAN               RGB(224, 255, 255)      // ����ɫ  
#define CLR_PALETURQUOISE           RGB(175, 238, 238)      // ���̱�ʯ  
#define CLR_CYAN                    RGB(  0, 255, 255)      // ��ɫ  
#define CLR_AQUA                    RGB(  0, 255, 255)      // ˮɫ  
#define CLR_DARKTURQUOISE           RGB(  0, 206, 209)      // ���̱�ʯ  
#define CLR_DARKSLATEGRAY           RGB( 47,  79,  79)      // ��ʯ���  
#define CLR_DARKCYAN                RGB(  0, 139, 139)      // ����ɫ  
#define CLR_TEAL                    RGB(  0, 128, 128)      // ˮѼɫ  
#define CLR_MEDIUMTURQUOISE         RGB( 72, 209, 204)      // ���̱�ʯ  
#define CLR_LIGHTSEAGREEN           RGB( 32, 178, 170)      // ǳ������  
#define CLR_TURQUOISE               RGB( 64, 224, 208)      // �̱�ʯ  
#define CLR_AQUAMARINE              RGB(127, 255, 212)      // ��ʯ����  
#define CLR_MEDIUMAQUAMARINE        RGB(102, 205, 170)      // �б�ʯ����  
#define CLR_MEDIUMSPRINGGREEN       RGB(  0, 250, 154)      // �д���ɫ  
#define CLR_MINTCREAM               RGB(245, 255, 250)      // ��������  
#define CLR_SPRINGGREEN             RGB(  0, 255, 127)      // ����ɫ  
#define CLR_MEDIUMSEAGREEN          RGB( 60, 179, 113)      // �к�����  
#define CLR_SEAGREEN                RGB( 46, 139,  87)      // ������  
#define CLR_HONEYDEW                RGB(240, 255, 240)      // �۹�ɫ  
#define CLR_LIGHTGREEN              RGB(144, 238, 144)      // ����ɫ  
#define CLR_PALEGREEN               RGB(152, 251, 152)      // ����ɫ  
#define CLR_DARKSEAGREEN            RGB(143, 188, 143)      // ��������  
#define CLR_LIMEGREEN               RGB( 50, 205,  50)      // ��������  
#define CLR_LIME                    RGB(  0, 255,   0)      // ������  
#define CLR_FORESTGREEN             RGB( 34, 139,  34)      // ɭ����  
#define CLR_GREEN                   RGB(  0, 128,   0)      // ����  
#define CLR_DARKGREEN               RGB(  0, 100,   0)      // ����ɫ  
#define CLR_CHARTREUSE              RGB(127, 255,   0)      // ���ؾ��� (����ɫ)  
#define CLR_LAWNGREEN               RGB(124, 252,   0)      // ��ƺ��  
#define CLR_GREENYELLOW             RGB(173, 255,  47)      // �̻�ɫ  
#define CLR_DARKOLIVEGREEN          RGB( 85, 107,  47)      // �������  
#define CLR_YELLOWGREEN             RGB(154, 205,  50)      // ����ɫ  
#define CLR_OLIVEDRAB               RGB(107, 142,  35)      // ��魺�ɫ  
#define CLR_BEIGE                   RGB(245, 245, 220)      // ��ɫ(����ɫ)  
#define CLR_LIGHTGOLDENRODYELLOW    RGB(250, 250, 210)      // ���ջ�  
#define CLR_IVORY                   RGB(255, 255, 240)      // ����  
#define CLR_LIGHTYELLOW             RGB(255, 255, 224)      // ǳ��ɫ  
#define CLR_YELLOW                  RGB(255, 255,   0)      // ����  
#define CLR_OLIVE                   RGB(128, 128,   0)      // ���  
#define CLR_DARKKHAKI               RGB(189, 183, 107)      // �ߴ��  
#define CLR_LEMONCHIFFON            RGB(255, 250, 205)      // ���ʳ�  
#define CLR_PALEGOLDENROD           RGB(238, 232, 170)      // �Ҿջ�  
#define CLR_KHAKI                   RGB(240, 230, 140)      // ��ߴ��  
#define CLR_GOLD                    RGB(255, 215,   0)      // ��ɫ  
#define CLR_CORNSILK                RGB(255, 248, 220)      // ����˿ɫ  
#define CLR_GOLDENROD               RGB(218, 165,  32)      // ��ջ�  
#define CLR_DARKGOLDENROD           RGB(184, 134,  11)      // ����ջ�  
#define CLR_FLORALWHITE             RGB(255, 250, 240)      // ���İ�ɫ  
#define CLR_OLDLACE                 RGB(253, 245, 230)      // ����˿  
#define CLR_WHEAT                   RGB(245, 222, 179)      // С��ɫ  
#define CLR_MOCCASIN                RGB(255, 228, 181)      // ¹Ƥѥ  
#define CLR_ORANGE                  RGB(255, 165,   0)      // ��ɫ  
#define CLR_PAPAYAWHIP              RGB(255, 239, 213)      // ��ľ��  
#define CLR_BLANCHEDALMOND          RGB(255, 235, 205)      // ���׵�����ɫ  
#define CLR_NAVAJOWHITE             RGB(255, 222, 173)      // ������  
#define CLR_ANTIQUEWHITE            RGB(250, 235, 215)      // �Ŷ���  
#define CLR_TAN                     RGB(210, 180, 140)      // ��ɫ  
#define CLR_BURLYWOOD               RGB(222, 184, 135)      // Ӳľɫ  
#define CLR_BISQUE                  RGB(255, 228, 196)      // ������  
#define CLR_DARKORANGE              RGB(255, 140,   0)      // ���ɫ  
#define CLR_LINEN                   RGB(250, 240, 230)      // ���鲼  
#define CLR_PERU                    RGB(205, 133,  63)      // ��³  
#define CLR_PEACHPUFF               RGB(255, 218, 185)      // ����ɫ  
#define CLR_SANDYBROWN              RGB(244, 164,  96)      // ɳ��ɫ  
#define CLR_CHOCOLATE               RGB(210, 105,  30)      // �ɿ���  
#define CLR_SADDLEBROWN             RGB(139,  69,  19)      // ����ɫ  
#define CLR_SEASHELL                RGB(255, 245, 238)      // ������  
#define CLR_SIENNA                  RGB(160,  82,  45)      // ������ɫ  
#define CLR_LIGHTSALMON             RGB(255, 160, 122)      // ǳ������ɫ  
#define CLR_CORAL                   RGB(255, 127,  80)      // ɺ��  
#define CLR_ORANGERED               RGB(255,  69,   0)      // �Ⱥ�ɫ  
#define CLR_DARKSALMON              RGB(233, 150, 122)      // ������(����)ɫ  
#define CLR_TOMATO                  RGB(255,  99,  71)      // ���Ѻ�  
#define CLR_MISTYROSE               RGB(255, 228, 225)      // ����õ��  
#define CLR_SALMON                  RGB(250, 128, 114)      // ����(����)ɫ  
#define CLR_SNOW                    RGB(255, 250, 250)      // ѩ  
#define CLR_LIGHTCORAL              RGB(240, 128, 128)      // ��ɺ��ɫ  
#define CLR_ROSYBROWN               RGB(188, 143, 143)      // õ����ɫ  
#define CLR_INDIANRED               RGB(205,  92,  92)      // ӡ�Ⱥ�  
#define CLR_RED                     RGB(255,   0,   0)      // ����  
#define CLR_BROWN                   RGB(165,  42,  42)      // ��ɫ  
#define CLR_FIREBRICK               RGB(178,  34,  34)      // �ͻ�ש  
#define CLR_DARKRED                 RGB(139,   0,   0)      // ���ɫ  
#define CLR_MAROON                  RGB(128,   0,   0)      // ��ɫ  
#define CLR_WHITE                   RGB(255, 255, 255)      // ����  
#define CLR_WHITESMOKE              RGB(245, 245, 245)      // ����  
#define CLR_GAINSBORO               RGB(220, 220, 220)      // ��˹���޻�ɫ  
#define CLR_LIGHTGREY               RGB(211, 211, 211)      // ǳ��ɫ  
#define CLR_SILVER                  RGB(192, 192, 192)      // ����ɫ  
#define CLR_DARKGRAY                RGB(169, 169, 169)      // ���ɫ  
#define CLR_GRAY                    RGB(186, 183, 186)      // ��ɫ(*)  
#define CLR_DIMGRAY                 RGB(105, 105, 105)      // �����Ļ�ɫ  
#define CLR_BLACK                   RGB(  0,   0,   0)      // ����


#pragma endregion


#define  WM_WALKRECORD_REFFRAME         (WM_USER + 1564)
#define  WM_WALKRECORD_QUIT             (WM_USER + 1565)
#define  WM_WALKRECORD_START            (WM_USER + 1566)


#pragma pack (1)
struct _tagWalkFrame {
	float x;
	float y;
	float z;

	float yaw;
};
#pragma pack ()
