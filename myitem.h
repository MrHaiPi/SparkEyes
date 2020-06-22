/**********************版权声明****************************

所有源代码由www.yafeilinux.com原创，我们遵循Qt开源版的所有相关条款和协议。

您有权使用，传播和更改我们的代码，但请保证代码的开源。

以下源代码版权归www.yafeilinux.com所有，请不要用作商业用途。


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
