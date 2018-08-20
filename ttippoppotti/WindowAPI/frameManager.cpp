#include "stdafx.h"
#include "frameManager.h"


HRESULT frameManager::init()
{
	return S_OK;
}

void frameManager::release()
{
}

void frameManager::frameChange(image* img, int& count, int& index, int &speed, bool isLeft)
{
	//�����������϶� �ε��� �����ϱ�(�ִϸ��̼�)
	if (isLeft)
	{
		count++;
		img->setFrameY(1);
		if ((count % speed) == 0)
		{
			index--;
			if (index < 0)
			{
				index = img->getMaxFrameX();
			}
			img->setFrameX(index);
		}
	}
	else//������������
	{
		count++;
		img->setFrameY(0);
		if ((count % speed) == 0)
		{
			index++;
			if (index > img->getMaxFrameX())
			{
				index = 0;
			}
			img->setFrameX(index);
		}
	}
}
