/**********************��Ȩ����****************************

����Դ������www.yafeilinux.comԭ����������ѭQt��Դ���������������Э�顣

����Ȩʹ�ã������͸������ǵĴ��룬���뱣֤����Ŀ�Դ��

����Դ�����Ȩ��www.yafeilinux.com���У��벻Ҫ������ҵ��;��


**********************************************************/

#ifndef MYITEM_H
#define MYITEM_H

class MyItem
{
public:
    MyItem();
    unsigned char* getItem();
    int currentItem_endPos(unsigned char *currentItem,unsigned char end);
    unsigned char* itemChange(unsigned char *currentItem);
};

#endif // MYITEM_H
