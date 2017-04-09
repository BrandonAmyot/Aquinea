#include "Seaweed.h"
using namespace std;


Seaweed::Seaweed(float rotAngle, glm::vec3 position)
{
	
		calculateSweep();
	
		//VAO, VBO, and EBO initialization
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		//Binding the VAO
		glBindVertexArray(VAO);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesVBO)*totalLength, verticesVBO, GL_STATIC_DRAW);

		//EBO Binding
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesEBO)*indexLength, indicesEBO, GL_STATIC_DRAW);

		//For the vertices (vertex shader)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		//For the colors (vertex shader)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//unbind the VAO
		glBindVertexArray(0);

		
		//Translate the weed to a position
		model = glm::translate(model, -position);
		
		//Apply the 90 degree rotation
		model = glm::rotate(model, glm::radians(rotAngle), glm::vec3(0, 0, 1));

		//Have to add a scale matrix
		

		//Compile the seaweed's shaders and load.
		shader = new Shader("res/shaders/seaweed.vs", "res/shaders/seaweed.fs");	
}



void Seaweed::render(glm::mat4 view, glm::mat4 projection)
{
	
	//Sin functiont to move the vertices based on time.
	//GLfloat timeMove = sin(glfwGetTime());
	//enabling the shader
	shader->use();

	GLuint transformLoc = glGetUniformLocation(shader->program, "model");
	GLuint viewMatrixLoc = glGetUniformLocation(shader->program, "view");
	GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");

	//model = glm::translate(model, timeMove*(glm::vec3(0, 1, 0)));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model)); 
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//Draw the seaweed
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexLength, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void Seaweed::calculateSweep()
{
	//the Profile and trajectory curve
	vector < glm::vec3> profile;
	vector < glm::vec3> trajectory;
	profile =
	{
		glm::vec3(-0.8475, -0.14, 0),
		glm::vec3(-0.83579, -0.138432, 0),
		glm::vec3(-0.841911, -0.139236, 0),
		glm::vec3(-0.822083, -0.136716, 0),
		glm::vec3(-0.83254, -0.138016, 0),
		glm::vec3(-0.812616, -0.135581, 0),
		glm::vec3(-0.822993, -0.136827, 0),
		glm::vec3(-0.807142, -0.134938, 0),
		glm::vec3(-0.815283, -0.135897, 0),
		glm::vec3(-0.802921, -0.134449, 0),
		glm::vec3(-0.809216, -0.135181, 0),
		glm::vec3(-0.789707, -0.132949, 0),
		glm::vec3(-0.799692, -0.134079, 0),
		glm::vec3(-0.779586, -0.131828, 0),
		glm::vec3(-0.78984, -0.132964, 0),
		glm::vec3(-0.774324, -0.131253, 0),
		glm::vec3(-0.782185, -0.132114, 0),
		glm::vec3(-0.758068, -0.129511, 0),
		glm::vec3(-0.770323, -0.13082, 0),
		glm::vec3(-0.756338, -0.129328, 0),
		glm::vec3(-0.763388, -0.130076, 0),
		glm::vec3(-0.741946, -0.127828, 0),
		glm::vec3(-0.752775, -0.128954, 0),
		glm::vec3(-0.732788, -0.12689, 0),
		glm::vec3(-0.742855, -0.127922, 0),
		glm::vec3(-0.72771, -0.126376, 0),
		glm::vec3(-0.735317, -0.127148, 0),
		glm::vec3(-0.712344, -0.124844, 0),
		glm::vec3(-0.723885, -0.125991, 0),
		glm::vec3(-0.702047, -0.123837, 0),
		glm::vec3(-0.712994, -0.124908, 0),
		glm::vec3(-0.696564, -0.123307, 0),
		glm::vec3(-0.704787, -0.124103, 0),
		glm::vec3(-0.68014, -0.121749, 0),
		glm::vec3(-0.692452, -0.122913, 0),
		glm::vec3(-0.678435, -0.121589, 0),
		glm::vec3(-0.685435, -0.122247, 0),
		glm::vec3(-0.664529, -0.120308, 0),
		glm::vec3(-0.674945, -0.121265, 0),
		glm::vec3(-0.655932, -0.119532, 0),
		glm::vec3(-0.665393, -0.120386, 0),
		glm::vec3(-0.651243, -0.119114, 0),
		glm::vec3(-0.658287, -0.119743, 0),
		glm::vec3(-0.637386, -0.117906, 0),
		glm::vec3(-0.647748, -0.118806, 0),
		glm::vec3(-0.624562, -0.116824, 0),
		glm::vec3(-0.636012, -0.117788, 0),
		glm::vec3(-0.618962, -0.116364, 0),
		glm::vec3(-0.627395, -0.11706, 0),
		glm::vec3(-0.602742, -0.115081, 0),
		glm::vec3(-0.614821, -0.116029, 0),
		glm::vec3(-0.601108, -0.114956, 0),
		glm::vec3(-0.607877, -0.115478, 0),
		glm::vec3(-0.588155, -0.114002, 0),
		glm::vec3(-0.597794, -0.114706, 0),
		glm::vec3(-0.580497, -0.113471, 0),
		glm::vec3(-0.58894, -0.114057, 0),
		glm::vec3(-0.565, -0.1125, 0),
		glm::vec3(-0.565, -0.1125, 0),
		glm::vec3(-0.551724, -0.11175, 0),
		glm::vec3(-0.558264, -0.112117, 0),
		glm::vec3(-0.539199, -0.111069, 0),
		glm::vec3(-0.548524, -0.111573, 0),
		glm::vec3(-0.531727, -0.110684, 0),
		glm::vec3(-0.539961, -0.11111, 0),
		glm::vec3(-0.516172, -0.109961, 0),
		glm::vec3(-0.527728, -0.110487, 0),
		glm::vec3(-0.513717, -0.10986, 0),
		glm::vec3(-0.520604, -0.110154, 0),
		glm::vec3(-0.500597, -0.109399, 0),
		glm::vec3(-0.510358, -0.109728, 0),
		glm::vec3(-0.492798, -0.109205, 0),
		glm::vec3(-0.501393, -0.109422, 0),
		glm::vec3(-0.476563, -0.109063, 0),
		glm::vec3(-0.488627, -0.109131, 0),
		glm::vec3(-0.467424, -0.109182, 0),
		glm::vec3(-0.477789, -0.109058, 0),
		glm::vec3(-0.462389, -0.109322, 0),
		glm::vec3(-0.469976, -0.109132, 0),
		glm::vec3(-0.447742, -0.110085, 0),
		glm::vec3(-0.458669, -0.109464, 0),
		glm::vec3(-0.434124, -0.111338, 0),
		glm::vec3(-0.446247, -0.110196, 0),
		glm::vec3(-0.428114, -0.112074, 0),
		glm::vec3(-0.437137, -0.111012, 0),
		glm::vec3(-0.423609, -0.112703, 0),
		glm::vec3(-0.430366, -0.111785, 0),
		glm::vec3(-0.41, -0.115, 0),
		glm::vec3(-0.41, -0.115, 0),
		glm::vec3(-0.393965, -0.118887, 0),
		glm::vec3(-0.40189, -0.11676, 0),
		glm::vec3(-0.378672, -0.124063, 0),
		glm::vec3(-0.390072, -0.120073, 0),
		glm::vec3(-0.369491, -0.127796, 0),
		glm::vec3(-0.379606, -0.123708, 0),
		glm::vec3(-0.364565, -0.129974, 0),
		glm::vec3(-0.371987, -0.126737, 0),
		glm::vec3(-0.350312, -0.136875, 0),
		glm::vec3(-0.360928, -0.131655, 0),
		glm::vec3(-0.344735, -0.139778, 0),
		glm::vec3(-0.352699, -0.135664, 0),
		glm::vec3(-0.340852, -0.141852, 0),
		glm::vec3(-0.346702, -0.138744, 0),
		glm::vec3(-0.3296, -0.148025, 0),
		glm::vec3(-0.337983, -0.143407, 0),
		glm::vec3(-0.319374, -0.153695, 0),
		glm::vec3(-0.328462, -0.148657, 0),
		glm::vec3(-0.314993, -0.156084, 0),
		glm::vec3(-0.321605, -0.152464, 0),
		glm::vec3(-0.3025, -0.1625, 0),
		glm::vec3(-0.3025, -0.1625, 0),
		glm::vec3(-0.286094, -0.171387, 0),
		glm::vec3(-0.293291, -0.167195, 0),
		glm::vec3(-0.274688, -0.178906, 0),
		glm::vec3(-0.283011, -0.173344, 0),
		glm::vec3(-0.26739, -0.183485, 0),
		glm::vec3(-0.275369, -0.178452, 0),
		glm::vec3(-0.262655, -0.186103, 0),
		glm::vec3(-0.269525, -0.18221, 0),
		glm::vec3(-0.258575, -0.188156, 0),
		glm::vec3(-0.264514, -0.185108, 0),
		glm::vec3(-0.2425, -0.195, 0),
		glm::vec3(-0.2425, -0.195, 0),
		glm::vec3(-0.228669, -0.20001, 0),
		glm::vec3(-0.235869, -0.197465, 0),
		glm::vec3(-0.212793, -0.205312, 0),
		glm::vec3(-0.224874, -0.20131, 0),
		glm::vec3(-0.202033, -0.208749, 0),
		glm::vec3(-0.213836, -0.204974, 0),
		glm::vec3(-0.19589, -0.210674, 0),
		glm::vec3(-0.205048, -0.207796, 0),
		glm::vec3(-0.191193, -0.212131, 0),
		glm::vec3(-0.198211, -0.209949, 0),
		glm::vec3(-0.176719, -0.216563, 0),
		glm::vec3(-0.187624, -0.213231, 0),
		glm::vec3(-0.165876, -0.219846, 0),
		glm::vec3(-0.176863, -0.216519, 0),
		glm::vec3(-0.160325, -0.22152, 0),
		glm::vec3(-0.168639, -0.219011, 0),
		glm::vec3(-0.156145, -0.22278, 0),
		glm::vec3(-0.16241, -0.220891, 0),
		glm::vec3(-0.143568, -0.226571, 0),
		glm::vec3(-0.153004, -0.223726, 0),
		glm::vec3(-0.139466, -0.227811, 0),
		glm::vec3(-0.146233, -0.225767, 0),
		glm::vec3(-0.126018, -0.231897, 0),
		glm::vec3(-0.13609, -0.228833, 0),
		glm::vec3(-0.117727, -0.234444, 0),
		glm::vec3(-0.126853, -0.231642, 0),
		glm::vec3(-0.11322, -0.23584, 0),
		glm::vec3(-0.119995, -0.233745, 0),
		glm::vec3(-0.1, -0.24, 0),
		glm::vec3(-0.1, -0.24, 0),
		glm::vec3(-0.0829126, -0.24604, 0),
		glm::vec3(-0.0912161, -0.24296, 0),
		glm::vec3(-0.0789049, -0.247617, 0),
		glm::vec3(-0.0849498, -0.24526, 0),
		glm::vec3(-0.0672852, -0.252461, 0),
		glm::vec3(-0.0759504, -0.248814, 0),
		glm::vec3(-0.0564381, -0.257196, 0),
		glm::vec3(-0.0660988, -0.252973, 0),
		glm::vec3(-0.0516035, -0.259316, 0),
		glm::vec3(-0.0588486, -0.256137, 0),
		glm::vec3(-0.0367187, -0.265625, 0),
		glm::vec3(-0.0479508, -0.260904, 0),
		glm::vec3(-0.029225, -0.268576, 0),
		glm::vec3(-0.0387947, -0.264776, 0),
		glm::vec3(-0.0242256, -0.270436, 0),
		glm::vec3(-0.0316666, -0.267635, 0),
		glm::vec3(-0.00808579, -0.275792, 0),
		glm::vec3(-0.0203629, -0.271809, 0),
		glm::vec3(-0.00628829, -0.276326, 0),
		glm::vec3(-0.0135084, -0.274104, 0),
		glm::vec3(0.00944781, -0.280506, 0),
		glm::vec3(-0.00252581, -0.277406, 0),
		glm::vec3(0.0203038, -0.282908, 0),
		glm::vec3(0.00840807, -0.280256, 0),
		glm::vec3(0.0266531, -0.28415, 0),
		glm::vec3(0.0172325, -0.282265, 0),
		glm::vec3(0.0316036, -0.285042, 0),
		glm::vec3(0.0242391, -0.283691, 0),
		glm::vec3(0.0475, -0.2875, 0),
		glm::vec3(0.0475, -0.2875, 0),
		glm::vec3(0.0627506, -0.289362, 0),
		glm::vec3(0.0548921, -0.288454, 0),
		glm::vec3(0.0797387, -0.29105, 0),
		glm::vec3(0.0668446, -0.2898, 0),
		glm::vec3(0.0911256, -0.292021, 0),
		glm::vec3(0.0786309, -0.290949, 0),
		glm::vec3(0.0976129, -0.292529, 0),
		glm::vec3(0.0879401, -0.29176, 0),
		glm::vec3(0.102575, -0.292897, 0),
		glm::vec3(0.0951626, -0.29234, 0),
		glm::vec3(0.11791, -0.293945, 0),
		glm::vec3(0.106348, -0.293168, 0),
		glm::vec3(0.129486, -0.294657, 0),
		glm::vec3(0.117757, -0.293935, 0),
		glm::vec3(0.135456, -0.295001, 0),
		glm::vec3(0.126527, -0.294481, 0),
		glm::vec3(0.139974, -0.295251, 0),
		glm::vec3(0.13321, -0.294873, 0),
		glm::vec3(0.153714, -0.295968, 0),
		glm::vec3(0.143385, -0.295436, 0),
		glm::vec3(0.15825, -0.296191, 0),
		glm::vec3(0.150783, -0.295821, 0),
		glm::vec3(0.173349, -0.296889, 0),
		glm::vec3(0.162006, -0.296371, 0),
		glm::vec3(0.182866, -0.297297, 0),
		glm::vec3(0.1724, -0.296847, 0),
		glm::vec3(0.188118, -0.297513, 0),
		glm::vec3(0.180244, -0.297187, 0),
		glm::vec3(0.203906, -0.298125, 0),
		glm::vec3(0.192062, -0.297671, 0),
		glm::vec3(0.215619, -0.298547, 0),
		glm::vec3(0.203847, -0.298123, 0),
		glm::vec3(0.221489, -0.298749, 0),
		glm::vec3(0.21268, -0.298443, 0),
		glm::vec3(0.22588, -0.298896, 0),
		glm::vec3(0.21929, -0.298674, 0),
		glm::vec3(0.238973, -0.299319, 0),
		glm::vec3(0.229166, -0.299005, 0),
		glm::vec3(0.243214, -0.29945, 0),
		glm::vec3(0.236212, -0.299232, 0),
		glm::vec3(0.257054, -0.299862, 0),
		glm::vec3(0.246697, -0.299556, 0),
		glm::vec3(0.265567, -0.300105, 0),
		glm::vec3(0.256196, -0.299837, 0),
		glm::vec3(0.270197, -0.300234, 0),
		glm::vec3(0.263238, -0.300039, 0),
		glm::vec3(0.283833, -0.300601, 0),
		glm::vec3(0.273643, -0.300328, 0),
		glm::vec3(0.297532, -0.300957, 0),
		glm::vec3(0.285768, -0.300653, 0),
		glm::vec3(0.303261, -0.301103, 0),
		glm::vec3(0.294628, -0.300883, 0),
		glm::vec3(0.307486, -0.301209, 0),
		glm::vec3(0.301125, -0.301049, 0),
		glm::vec3(0.319758, -0.301516, 0),
		glm::vec3(0.310612, -0.301288, 0),
		glm::vec3(0.323624, -0.301613, 0),
		glm::vec3(0.317212, -0.301453, 0),
		glm::vec3(0.33584, -0.30192, 0),
		glm::vec3(0.326756, -0.301691, 0),
		glm::vec3(0.343028, -0.302106, 0),
		glm::vec3(0.335102, -0.301902, 0),
		glm::vec3(0.3575, -0.3025, 0),
		glm::vec3(0.3575, -0.3025, 0),
		glm::vec3(0.382046, -0.302957, 0),
		glm::vec3(0.370412, -0.302806, 0),
		glm::vec3(0.387424, -0.30298, 0),
		glm::vec3(0.37925, -0.302932, 0),
		glm::vec3(0.401992, -0.302871, 0),
		glm::vec3(0.391278, -0.302976, 0),
		glm::vec3(0.414061, -0.302565, 0),
		glm::vec3(0.403387, -0.302846, 0),
		glm::vec3(0.418945, -0.302381, 0),
		glm::vec3(0.411512, -0.302647, 0),
		glm::vec3(0.432188, -0.301719, 0),
		glm::vec3(0.422437, -0.302228, 0),
		glm::vec3(0.437966, -0.301374, 0),
		glm::vec3(0.43049, -0.301815, 0),
		glm::vec3(0.452029, -0.300541, 0),
		glm::vec3(0.441553, -0.301154, 0),
		glm::vec3(0.460823, -0.30015, 0),
		glm::vec3(0.451161, -0.300588, 0),
		glm::vec3(0.465845, -0.300005, 0),
		glm::vec3(0.458372, -0.300242, 0),
		glm::vec3(0.4825, -0.3, 0),
		glm::vec3(0.4825, -0.3, 0),
		glm::vec3(0.497935, -0.30063, 0),
		glm::vec3(0.490118, -0.30024, 0),
		glm::vec3(0.513945, -0.301758, 0),
		glm::vec3(0.5019, -0.300873, 0),
		glm::vec3(0.524049, -0.302625, 0),
		glm::vec3(0.512936, -0.301677, 0),
		glm::vec3(0.52959, -0.303132, 0),
		glm::vec3(0.521271, -0.302378, 0),
		glm::vec3(0.545938, -0.304688, 0),
		glm::vec3(0.533725, -0.30352, 0),
		glm::vec3(0.552395, -0.305298, 0),
		glm::vec3(0.543178, -0.304423, 0),
		glm::vec3(0.556886, -0.305711, 0),
		glm::vec3(0.550118, -0.305085, 0),
		glm::vec3(0.569746, -0.306786, 0),
		glm::vec3(0.560192, -0.306005, 0),
		glm::vec3(0.580983, -0.307482, 0),
		glm::vec3(0.571024, -0.30688, 0),
		glm::vec3(0.585574, -0.307652, 0),
		glm::vec3(0.578586, -0.307362, 0),
		glm::vec3(0.5975, -0.3075, 0),
		glm::vec3(0.5975, -0.3075, 0),
		glm::vec3(0.615937, -0.301094, 0),
		glm::vec3(0.610273, -0.305176, 0),
		glm::vec3(0.6275, -0.29, 0),
		glm::vec3(0.6275, -0.29, 0),
		glm::vec3(0.640098, -0.283731, 0),
		glm::vec3(0.633479, -0.286951, 0),
		glm::vec3(0.654844, -0.276719, 0),
		glm::vec3(0.643615, -0.282052, 0),
		glm::vec3(0.664787, -0.271907, 0),
		glm::vec3(0.653875, -0.277181, 0),
		glm::vec3(0.670404, -0.269108, 0),
		glm::vec3(0.662012, -0.273266, 0),
		glm::vec3(0.67466, -0.266933, 0),
		glm::vec3(0.668288, -0.270171, 0),
		glm::vec3(0.6875, -0.26, 0),
		glm::vec3(0.6875, -0.26, 0),
		glm::vec3(0.705273, -0.249453, 0),
		glm::vec3(0.696118, -0.25499, 0),
		glm::vec3(0.709988, -0.246542, 0),
		glm::vec3(0.702946, -0.250877, 0),
		glm::vec3(0.713564, -0.244314, 0),
		glm::vec3(0.708212, -0.247642, 0),
		glm::vec3(0.724375, -0.2375, 0),
		glm::vec3(0.71626, -0.242624, 0),
		glm::vec3(0.727897, -0.235264, 0),
		glm::vec3(0.722083, -0.238952, 0),
		glm::vec3(0.739308, -0.227998, 0),
		glm::vec3(0.730785, -0.233427, 0),
		glm::vec3(0.746165, -0.223644, 0),
		glm::vec3(0.738608, -0.228444, 0),
		glm::vec3(0.749805, -0.221345, 0),
		glm::vec3(0.744307, -0.224821, 0),
		glm::vec3(0.76, -0.215, 0)
	};

	trajectory =
	{
		glm::vec3(-0.8, 0, -0.0375),
		glm::vec3(-0.787969, 0, -0.0245703),
		glm::vec3(-0.793994, 0, -0.0314795),
		glm::vec3(-0.784857, 0, -0.0208832),
		glm::vec3(-0.789493, 0, -0.0263634),
		glm::vec3(-0.774688, 0, -0.00937498),
		glm::vec3(-0.78245, 0, -0.0180491),
		glm::vec3(-0.773529, 0, -0.00816762),
		glm::vec3(-0.778145, 0, -0.0131243),
		glm::vec3(-0.763058, 0, 0.00150293),
		glm::vec3(-0.77108, 0, -0.00570381),
		glm::vec3(-0.755452, 0, 0.00713873),
		glm::vec3(-0.763769, 0, 0.000917435),
		glm::vec3(-0.750854, 0, 0.0100305),
		glm::vec3(-0.757637, 0, 0.005633),
		glm::vec3(-0.747192, 0, 0.012081),
		glm::vec3(-0.752615, 0, 0.00896591),
		glm::vec3(-0.735, 0, 0.0175),
		glm::vec3(-0.735, 0, 0.0175),
		glm::vec3(-0.720322, 0, 0.0220557),
		glm::vec3(-0.727997, 0, 0.0198492),
		glm::vec3(-0.716258, 0, 0.0231065),
		glm::vec3(-0.722299, 0, 0.0215173),
		glm::vec3(-0.703281, 0, 0.0260547),
		glm::vec3(-0.71312, 0, 0.0238721),
		glm::vec3(-0.689934, 0, 0.0286016),
		glm::vec3(-0.701869, 0, 0.0263445),
		glm::vec3(-0.683763, 0, 0.0296517),
		glm::vec3(-0.692973, 0, 0.0280569),
		glm::vec3(-0.679062, 0, 0.0304058),
		glm::vec3(-0.686091, 0, 0.0292639),
		glm::vec3(-0.664688, 0, 0.0325),
		glm::vec3(-0.675503, 0, 0.0309528),
		glm::vec3(-0.652649, 0, 0.0340441),
		glm::vec3(-0.664142, 0, 0.0325738),
		glm::vec3(-0.64689, 0, 0.0347244),
		glm::vec3(-0.655528, 0, 0.0336903),
		glm::vec3(-0.642576, 0, 0.035211),
		glm::vec3(-0.649049, 0, 0.0344734),
		glm::vec3(-0.629736, 0, 0.0365538),
		glm::vec3(-0.639349, 0, 0.0355631),
		glm::vec3(-0.625597, 0, 0.0369548),
		glm::vec3(-0.632438, 0, 0.0362838),
		glm::vec3(-0.612232, 0, 0.0381517),
		glm::vec3(-0.622211, 0, 0.0372719),
		glm::vec3(-0.604168, 0, 0.0388052),
		glm::vec3(-0.613052, 0, 0.0380824),
		glm::vec3(-0.599851, 0, 0.0391348),
		glm::vec3(-0.60636, 0, 0.0386326),
		glm::vec3(-0.5875, 0, 0.04),
		glm::vec3(-0.5875, 0, 0.04),
		glm::vec3(-0.57127, 0, 0.0406909),
		glm::vec3(-0.579268, 0, 0.0404428),
		glm::vec3(-0.555859, 0, 0.0406836),
		glm::vec3(-0.567349, 0, 0.0407482),
		glm::vec3(-0.54654, 0, 0.040396),
		glm::vec3(-0.556803, 0, 0.0407014),
		glm::vec3(-0.541492, 0, 0.0401627),
		glm::vec3(-0.549084, 0, 0.0404938),
		glm::vec3(-0.526563, 0, 0.0392187),
		glm::vec3(-0.537734, 0, 0.0399578),
		glm::vec3(-0.520534, 0, 0.0387589),
		glm::vec3(-0.529105, 0, 0.0394018),
		glm::vec3(-0.516253, 0, 0.0384157),
		glm::vec3(-0.522674, 0, 0.0389259),
		glm::vec3(-0.50336, 0, 0.0373505),
		glm::vec3(-0.51304, 0, 0.0381523),
		glm::vec3(-0.49081, 0, 0.0363619),
		glm::vec3(-0.502008, 0, 0.0372396),
		glm::vec3(-0.485117, 0, 0.0359587),
		glm::vec3(-0.493631, 0, 0.0365741),
		glm::vec3(-0.480794, 0, 0.0356793),
		glm::vec3(-0.48726, 0, 0.0361062),
		glm::vec3(-0.4675, 0, 0.035),
		glm::vec3(-0.4675, 0, 0.035),
		glm::vec3(-0.451587, 0, 0.0345801),
		glm::vec3(-0.459576, 0, 0.0347424),
		glm::vec3(-0.43543, 0, 0.0344532),
		glm::vec3(-0.447569, 0, 0.0345277),
		glm::vec3(-0.42522, 0, 0.0344445),
		glm::vec3(-0.436446, 0, 0.0344559),
		glm::vec3(-0.419572, 0, 0.0344437),
		glm::vec3(-0.428036, 0, 0.0344447),
		glm::vec3(-0.415322, 0, 0.0344393),
		glm::vec3(-0.421693, 0, 0.0344443),
		glm::vec3(-0.4025, 0, 0.034375),
		glm::vec3(-0.412126, 0, 0.0344319),
		glm::vec3(-0.393075, 0, 0.0342441),
		glm::vec3(-0.402626, 0, 0.0343761),
		glm::vec3(-0.388282, 0, 0.0341389),
		glm::vec3(-0.395467, 0, 0.0342861),
		glm::vec3(-0.373841, 0, 0.0336187),
		glm::vec3(-0.38468, 0, 0.0340397),
		glm::vec3(-0.359928, 0, 0.0327513),
		glm::vec3(-0.372332, 0, 0.0335438),
		glm::vec3(-0.353709, 0, 0.0322222),
		glm::vec3(-0.363034, 0, 0.0329809),
		glm::vec3(-0.349039, 0, 0.0317603),
		glm::vec3(-0.356043, 0, 0.032432),
		glm::vec3(-0.335, 0, 0.03),
		glm::vec3(-0.335, 0, 0.03),
		glm::vec3(-0.317654, 0, 0.0270947),
		glm::vec3(-0.326401, 0, 0.0286456),
		glm::vec3(-0.313233, 0, 0.0262513),
		glm::vec3(-0.319853, 0, 0.0274999),
		glm::vec3(-0.299824, 0, 0.0234765),
		glm::vec3(-0.3099, 0, 0.0255908),
		glm::vec3(-0.286834, 0, 0.0205177),
		glm::vec3(-0.298417, 0, 0.0231681),
		glm::vec3(-0.281022, 0, 0.019119),
		glm::vec3(-0.289736, 0, 0.0211994),
		glm::vec3(-0.27666, 0, 0.018042),
		glm::vec3(-0.283202, 0, 0.0196487),
		glm::vec3(-0.263594, 0, 0.0146875),
		glm::vec3(-0.27339, 0, 0.0172196),
		glm::vec3(-0.252879, 0, 0.0118106),
		glm::vec3(-0.263105, 0, 0.0145585),
		glm::vec3(-0.2478, 0, 0.0104125),
		glm::vec3(-0.255427, 0, 0.0125043),
		glm::vec3(-0.232762, 0, 0.00616157),
		glm::vec3(-0.24401, 0, 0.00935608),
		glm::vec3(-0.231217, 0, 0.00571632),
		glm::vec3(-0.237581, 0, 0.00754011),
		glm::vec3(-0.218728, 0, 0.00207281),
		glm::vec3(-0.228063, 0, 0.00480354),
		glm::vec3(-0.211114, 0, -0.000181198),
		glm::vec3(-0.219498, 0, 0.00229955),
		glm::vec3(-0.206999, 0, -0.00140715),
		glm::vec3(-0.213191, 0, 0.000435889),
		glm::vec3(-0.195, 0, -0.005),
		glm::vec3(-0.195, 0, -0.005),
		glm::vec3(-0.18002, 0, -0.00982904),
		glm::vec3(-0.187356, 0, -0.00738096),
		glm::vec3(-0.166094, 0, -0.0148828),
		glm::vec3(-0.176453, 0, -0.0110749),
		glm::vec3(-0.157769, 0, -0.0181164),
		glm::vec3(-0.16694, 0, -0.014562),
		glm::vec3(-0.153277, 0, -0.0199097),
		glm::vec3(-0.160036, 0, -0.0172231),
		glm::vec3(-0.14, 0, -0.0253125),
		glm::vec3(-0.149937, 0, -0.0212591),
		glm::vec3(-0.134615, 0, -0.027506),
		glm::vec3(-0.142265, 0, -0.0243866),
		glm::vec3(-0.119084, 0, -0.0336447),
		glm::vec3(-0.130776, 0, -0.0290567),
		glm::vec3(-0.109004, 0, -0.0373601),
		glm::vec3(-0.120072, 0, -0.0332669),
		glm::vec3(-0.103273, 0, -0.0393475),
		glm::vec3(-0.111816, 0, -0.0363505),
		glm::vec3(-0.0988688, 0, -0.040807),
		glm::vec3(-0.10544, 0, -0.0386074),
		glm::vec3(-0.085, 0, -0.045),
		glm::vec3(-0.085, 0, -0.045),
		glm::vec3(-0.0691919, 0, -0.049314),
		glm::vec3(-0.0771427, 0, -0.0471725),
		glm::vec3(-0.0529883, 0, -0.0534961),
		glm::vec3(-0.0651798, 0, -0.0503725),
		glm::vec3(-0.0426406, 0, -0.0560365),
		glm::vec3(-0.0540134, 0, -0.0532389),
		glm::vec3(-0.0368724, 0, -0.057408),
		glm::vec3(-0.045504, 0, -0.0553439),
		glm::vec3(-0.0325089, 0, -0.0584241),
		glm::vec3(-0.0390421, 0, -0.0568959),
		glm::vec3(-0.0192187, 0, -0.0614063),
		glm::vec3(-0.0292148, 0, -0.0591792),
		glm::vec3(-0.00931305, 0, -0.0635184),
		glm::vec3(-0.0193503, 0, -0.0613775),
		glm::vec3(-0.00422692, 0, -0.0645664),
		glm::vec3(-0.0118391, 0, -0.0629888),
		glm::vec3(0.0113127, 0, -0.0676162),
		glm::vec3(-0.000382066, 0, -0.0653423),
		glm::vec3(0.0129565, 0, -0.0679255),
		glm::vec3(0.00624752, 0, -0.0666471),
		glm::vec3(0.0266216, 0, -0.0704002),
		glm::vec3(0.0163416, 0, -0.0685546),
		glm::vec3(0.0353357, 0, -0.071889),
		glm::vec3(0.0257577, 0, -0.0702488),
		glm::vec3(0.0401871, 0, -0.0726883),
		glm::vec3(0.0329258, 0, -0.0714841),
		glm::vec3(0.0549999, 0, -0.075),
		glm::vec3(0.0549999, 0, -0.075),
		glm::vec3(0.0753418, 0, -0.0779053),
		glm::vec3(0.06505, 0, -0.0764691),
		glm::vec3(0.0805714, 0, -0.0786098),
		glm::vec3(0.0727475, 0, -0.0775495),
		glm::vec3(0.0965625, 0, -0.080664),
		glm::vec3(0.0845281, 0, -0.079132),
		glm::vec3(0.0982522, 0, -0.0808725),
		glm::vec3(0.091352, 0, -0.080011),
		glm::vec3(0.112259, 0, -0.08254),
		glm::vec3(0.101729, 0, -0.0812967),
		glm::vec3(0.121137, 0, -0.0835418),
		glm::vec3(0.111377, 0, -0.0824381),
		glm::vec3(0.126055, 0, -0.0840783),
		glm::vec3(0.118687, 0, -0.0832695),
		glm::vec3(0.140937, 0, -0.0856251),
		glm::vec3(0.129758, 0, -0.0844742),
		glm::vec3(0.142444, 0, -0.085775),
		glm::vec3(0.136086, 0, -0.0851336),
		glm::vec3(0.155237, 0, -0.0870012),
		glm::vec3(0.145633, 0, -0.0860888),
		glm::vec3(0.163273, 0, -0.0877273),
		glm::vec3(0.154434, 0, -0.0869269),
		glm::vec3(0.167702, 0, -0.0881131),
		glm::vec3(0.16106, 0, -0.0875307),
		glm::vec3(0.181019, 0, -0.089209),
		glm::vec3(0.171028, 0, -0.0883956),
		glm::vec3(0.186448, 0, -0.089628),
		glm::vec3(0.178735, 0, -0.0890276),
		glm::vec3(0.201868, 0, -0.0907286),
		glm::vec3(0.190305, 0, -0.0899158),
		glm::vec3(0.211483, 0, -0.091346),
		glm::vec3(0.200906, 0, -0.0906639),
		glm::vec3(0.216758, 0, -0.0916611),
		glm::vec3(0.208842, 0, -0.0911818),
		glm::vec3(0.2325, 0, -0.0925),
		glm::vec3(0.2325, 0, -0.0925),
		glm::vec3(0.255898, 0, -0.0935596),
		glm::vec3(0.244026, 0, -0.0930401),
		glm::vec3(0.261942, 0, -0.0938082),
		glm::vec3(0.252902, 0, -0.0934323),
		glm::vec3(0.266514, 0, -0.0939883),
		glm::vec3(0.259668, 0, -0.093716),
		glm::vec3(0.280391, 0, -0.0944922),
		glm::vec3(0.269962, 0, -0.0941199),
		glm::vec3(0.28496, 0, -0.0946428),
		glm::vec3(0.277435, 0, -0.0943905),
		glm::vec3(0.300104, 0, -0.0950807),
		glm::vec3(0.288737, 0, -0.094761),
		glm::vec3(0.309586, 0, -0.0953031),
		glm::vec3(0.299156, 0, -0.0950562),
		glm::vec3(0.314792, 0, -0.0954061),
		glm::vec3(0.30698, 0, -0.0952462),
		glm::vec3(0.330312, 0, -0.095625),
		glm::vec3(0.318689, 0, -0.0954739),
		glm::vec3(0.332538, 0, -0.0956445),
		glm::vec3(0.325635, 0, -0.0955738),
		glm::vec3(0.346163, 0, -0.0956908),
		glm::vec3(0.335969, 0, -0.0956683),
		glm::vec3(0.354519, 0, -0.0956498),
		glm::vec3(0.34532, 0, -0.0956918),
		glm::vec3(0.359053, 0, -0.0956028),
		glm::vec3(0.352236, 0, -0.0956668),
		glm::vec3(0.372334, 0, -0.0953492),
		glm::vec3(0.36242, 0, -0.0955553),
		glm::vec3(0.377587, 0, -0.0951951),
		glm::vec3(0.370094, 0, -0.095405),
		glm::vec3(0.391938, 0, -0.094583),
		glm::vec3(0.381258, 0, -0.0950667),
		glm::vec3(0.400417, 0, -0.0940613),
		glm::vec3(0.391069, 0, -0.0946292),
		glm::vec3(0.4049, 0, -0.0937256),
		glm::vec3(0.398126, 0, -0.094216),
		glm::vec3(0.4175, 0, -0.0925),
		glm::vec3(0.4175, 0, -0.0925),
		glm::vec3(0.433779, 0, -0.0900439),
		glm::vec3(0.4259, 0, -0.0913751),
		glm::vec3(0.448125, 0, -0.086836),
		glm::vec3(0.437536, 0, -0.0893068),
		glm::vec3(0.456239, 0, -0.0845141),
		glm::vec3(0.447279, 0, -0.0870557),
		glm::vec3(0.460455, 0, -0.0831493),
		glm::vec3(0.454068, 0, -0.0851741),
		glm::vec3(0.472188, 0, -0.07875),
		glm::vec3(0.463511, 0, -0.0820894),
		glm::vec3(0.476625, 0, -0.0768543),
		glm::vec3(0.470265, 0, -0.079532),
		glm::vec3(0.488413, 0, -0.0712616),
		glm::vec3(0.479677, 0, -0.07548),
		glm::vec3(0.495328, 0, -0.0676955),
		glm::vec3(0.487706, 0, -0.0716169),
		glm::vec3(0.499037, 0, -0.0657381),
		glm::vec3(0.493452, 0, -0.0686768),
		glm::vec3(0.51, 0, -0.0599999),
		glm::vec3(0.51, 0, -0.0599999),
		glm::vec3(0.525254, 0, -0.0509961),
		glm::vec3(0.518215, 0, -0.0554956),
		glm::vec3(0.537031, 0, -0.0417187),
		glm::vec3(0.528428, 0, -0.0487252),
		glm::vec3(0.54372, 0, -0.0355213),
		glm::vec3(0.53635, 0, -0.0423176),
		glm::vec3(0.547448, 0, -0.0319177),
		glm::vec3(0.541886, 0, -0.0372672),
		glm::vec3(0.550344, 0, -0.0291057),
		glm::vec3(0.546036, 0, -0.0332875),
		glm::vec3(0.56, 0, -0.02),
		glm::vec3(0.56, 0, -0.02),
		glm::vec3(0.57418, 0, -0.00664067),
		glm::vec3(0.566987, 0, -0.0135254),
		glm::vec3(0.577844, 0, -0.00306273),
		glm::vec3(0.572364, 0, -0.0083971),
		glm::vec3(0.589062, 0, 0.00812501),
		glm::vec3(0.580618, 0, -0.000326037),
		glm::vec3(0.590248, 0, 0.00932413),
		glm::vec3(0.585406, 0, 0.0044452),
		glm::vec3(0.600063, 0, 0.019344),
		glm::vec3(0.592687, 0, 0.0117992),
		glm::vec3(0.606263, 0, 0.0257394),
		glm::vec3(0.599445, 0, 0.0187092),
		glm::vec3(0.609689, 0, 0.029287),
		glm::vec3(0.604554, 0, 0.0239729),
		glm::vec3(0.62, 0, 0.04),
		glm::vec3(0.62, 0, 0.04),
		glm::vec3(0.636484, 0, 0.0571485),
		glm::vec3(0.628057, 0, 0.048374),
		glm::vec3(0.640782, 0, 0.06164),
		glm::vec3(0.634352, 0, 0.0549253),
		glm::vec3(0.644025, 0, 0.0650393),
		glm::vec3(0.639166, 0, 0.0599493),
		glm::vec3(0.65375, 0, 0.0753125),
		glm::vec3(0.646461, 0, 0.0676008),
		glm::vec3(0.656894, 0, 0.078665),
		glm::vec3(0.651698, 0, 0.0731336),
		glm::vec3(0.667002, 0, 0.0895929),
		glm::vec3(0.659463, 0, 0.0814199),
		glm::vec3(0.673017, 0, 0.0962383),
		glm::vec3(0.666386, 0, 0.0889189),
		glm::vec3(0.676192, 0, 0.0998042),
		glm::vec3(0.671392, 0, 0.0944298),
		glm::vec3(0.685, 0, 0.11)
	};


	//Size, which is the profile vector size times the trajectory vect size times 6 
	totalLength = profile.size()*trajectory.size() * 6;
	verticesVBO = new GLfloat[totalLength];

	//A position which we will need to keep for the indices
	int pos = 0;
	int counterEBO = 0;

	//gets the size of the EBO
	indexLength = (profile.size() - 1)*(trajectory.size() - 1) * 6;
	indicesEBO = new int[indexLength];

	//Translating the profile and trajectory vertices
	for (int i = 0; i < profile.size(); i++)
	{
		for (int k = 0; k < trajectory.size(); k++)
		{
			float colour = (float(i) / float(profile.size()));

			verticesVBO[pos] = profile.at(i).x + trajectory.at(k).x;
			verticesVBO[pos + 1] = profile.at(i).y + trajectory.at(k).y;
			verticesVBO[pos + 2] = profile.at(i).z + trajectory.at(k).z;
			verticesVBO[pos + 3] = colour * 0.1;
			verticesVBO[pos + 4] = colour * 0.39;
			verticesVBO[pos + 5] = 0;
			//increment the pos value in order to find the next set of vertices
			pos += 6;
			//If we are after the first iteration of i and k, then it means we are ontop.
			//Now we have to store the indices for the EBO in order to draw the triangles
			if (i > 0 && k > 0)
			{
				//Getting the indices for the EBO
				indicesEBO[counterEBO] = pos / 6 - 1;
				indicesEBO[counterEBO + 1] = pos / 6 - 1 - 1;
				indicesEBO[counterEBO + 2] = pos / 6 - trajectory.size() - 2;
				indicesEBO[counterEBO + 3] = pos / 6 - 1;
				indicesEBO[counterEBO + 4] = pos / 6 - trajectory.size() - 1;
				indicesEBO[counterEBO + 5] = pos / 6 - trajectory.size() - 2;
				//Increment the counter in order to find the next set of indices
				counterEBO += 6;
			}
		}
	}
}
