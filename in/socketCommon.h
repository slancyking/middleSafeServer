#pragma once

namespace socketCommon {
	/// <summary>
	/// �ж϶˿��Ƿ�ռ��
	/// </summary>
	/// <param name="nPort">�˿ں�</param>
	/// <returns>����ʹ��״̬,ʹ�÷���1,δʹ�÷���0</returns>
	bool GetSocketPortState(USHORT nPort);

	///�����ȡһ��δʹ�õĶ˿�
	USHORT getRandPortUnuse();
}

