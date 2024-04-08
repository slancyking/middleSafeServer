#pragma once

namespace socketCommon {
	/// <summary>
	/// 判断端口是否被占用
	/// </summary>
	/// <param name="nPort">端口号</param>
	/// <returns>返回使用状态,使用返回1,未使用返回0</returns>
	bool GetSocketPortState(USHORT nPort);

	///随机获取一个未使用的端口
	USHORT getRandPortUnuse();
}

