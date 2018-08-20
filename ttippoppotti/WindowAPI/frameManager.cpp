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
	//왼쪽프레임일때 인덱스 변경하기(애니메이션)
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
	else//오른쪽프레임
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
