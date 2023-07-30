#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "game.h"
#include "resource_manager.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* windoe, int key, int scancode, int action, int mode);



const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc,char* argv[]) {
	glfwInit();//初始化glfw，为一些空指针赋值 。
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//设置glfw库的一些属性，name为属性字段，value为设置的值。
		//GLFW_CONTEXT_VERSION_MAJOR指OpenGL主版本号。
		//GLFW_CONTEXT_VERSION_MINOR指OpenGL次版本号。
		//GLFW_OPENGL_PROFILE指渲染模式， GLFW_OPENGL_CORE_PROFILE为核心模式。
		//GLFW_RESIZABLE表示窗口可调性， GL_FALSE代表不可调。
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__如果使用的是Mac OS X系统，你还需要加下面这行代码到你的初始化代码中这些配置才能起作用（将上面的代码解除注释）
	glfwWindowHint(GLFW_RESIZABLE, false);
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);//创建一个glfw窗口，参数为：宽、高、窗口标题。返GLFWwindow* 类型。
	glfwMakeContextCurrent(window);// 通知GLFW将窗口window的上下文设置为当前线程的主上下文。

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);//	通过GLFW注册函数至合适的回调，callback为函数名。
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 我们还需要注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数：


	//配置opengl
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//x，y 以像素为单位，指定了视口的左下角位置。
	//width，height 表示这个视口矩形的宽度和高度，根据窗口的实时变化重绘窗口。
	glEnable(GL_BLEND);//用于启用各种功能,GL_BLEND启用颜色混合。例如实现半透明效果
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//	把源颜色和目标颜色各自取出，并乘以一个系数（源颜色乘以的系数称为“源因子”，目标颜色乘以的系数称为“目标因子”），然后相加，这样就得到了新的颜色。
	//GL_SRC_COLOR   表示使用源颜色的alpha值来作为因子
	//GL_ONE_MINUS_SRC_ALPHA       表示用1.0减去源颜色的alpha值来作为因子
	

	//初始化game
	Breakout.Init();

	//deltatime variables
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))//每次循环的开始前检查一次GLFW是否被要求退出
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame - lastFrame;
		glfwPollEvents();//函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
		
		//管理用户输入
		Breakout.ProcessInput(deltaTime);

		//更新游戏状态
		Breakout.Update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//设置清空屏幕所用的颜色。
		glClear(GL_COLOR_BUFFER_BIT);// 清空屏幕的颜色缓冲。
		Breakout.Render();

		glfwSwapBuffers(window); //交换两个缓冲区的内容
		
	}

	ResourceManager::Clear();
	glfwTerminate();//释放GLFW分配的内存

	return 0;


}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key==GLFW_KEY_ESCAPE&&action ==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (key>=0&&key<1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = true;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = false;
	}
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

