import numpy as np
import matplotlib.pyplot as plt

def plotf(fromX,toX,shagX,funct,labelX,labelY,title,legend):
	'''
	Строит график
	:fromX: от Х
	:toX: до Х
	:shagX: шаг по X
	:funct: f(x)
	:labelX: подпись оси X
	:labelY: подпись оси Y
	:title: заголовок
	:legend: легенда
	'''
	arX = np.arange(fromX,toX,shagX)
	arY = list()

	for x in arX:
		arY.append(funct(x))

	plt.figure(figsize=[9,6])
	plt.plot(arX, arY, linewidth=2)
	#plt.yscale('log');
	plt.grid(True, color='#DDDDDD', linestyle='--', which='both')
	plt.ylabel(labelY)
	plt.xlabel(labelX)
	plt.title(title)
	plt.legend(legend)
	#plt.xlim([1, 90])
	plt.show()

class Atom:
	def __init__(self,A,Z):
		'''
		Инициализация основных значений для последующего вычисления
		:param A:  Type is Integer. Массовое число A
		:param Z:  Type is Integer. Зарядовое число Z
		'''
		self.A = A
		self.Z = Z


	def mass(self):
		'''
		Вычисление массы с использованием энергии связи ядра, рассчитаной по формуле Вайцзекера
		:return: возвращается масса ядра (а.е.м.)
		'''
		delta_MH1 = 7.289 #дефект массы водорода (Мэв)
		delta_mn = 8.071 #дефект массы нейтрона (Мэв)
		#используя Gя =Z*delta_MH1 + (A-Z)*delta_mn – delta_M(A,Z) получим:
		delta_M = (self.Z*delta_MH1 + (self.A-self.Z)*delta_mn-self.g_energy())
		return(self.A*931.5+delta_M)
	
	
	def g_energy(self):
		'''
		Вычисление энергии связи ядра, рассчитаной по формуле Вайцзекера
		:return: возвращается энергия связи ядра (МэВ)
        '''
		a1 = 15.6
		a2 = 17.2
		a3 = 0.72
		a4 = 23.6
		if (self.A % 2 == 0 and self.Z % 2 == 0):
			a5 = 34 #если ядро четно четное
		elif(self.A % 2 == 1 and self.Z % 2 == 1):
			a5 = -34 #если ядро нечетно нечетное
		else:
			a5 = 0 #в остальных случаях
		return(a1*self.A-a2*np.power(self.A,2/3)-a3*self.Z*(self.Z-1)*np.power(self.A,-1/3)-a4*(np.power(self.A-2*self.Z,2)/self.A)+a5*np.power(self.A,-3/4))
	
	
	def r(self):
		'''
		Вычисление радиуса ядра по приближенной формуле
		r = r0 * A^1/3
		:return: возвращается радиус (Фм)
		'''
		return(1.1*np.power(self.A,(1/3)))
	
	
	def canBeta(self):
		'''
		Оценивает способность ядра к beta распаду
		:return: возвращается True если устойчив, иначе False
		'''
		Z0 = self.A/(0.015*np.power(self.A,(2/3))+1.98) #линия стабильности ядер
		if(abs(self.Z-Z0) > 3.0):
			return(0) #если отклонение от линии стабильности велико
		else:
			return(1) #если отклонение мало
			
			
	def canHalf(self):
		'''
		Оценивает, возможно ли деление данного изотопа на 2 одинаковых четно-четных осколка.
		:return: возвращается True если распадается, иначе False
		'''
		if((self.A % 4 != 0) and (self.Z % 4 != 0)):
			return(False) #если не могут образоваться четно-четные осколки
		else:
			E =  self.mass()-2*Atom(self.A//2,self.Z//2).mass() #оценка энерговыделения реакции
			if (E >= 0):
				return(True) #если энерговыделение положительно
			else:
				return(False)
				
				
	def dataPrint(self):
		'''
		Выводит в консоль информацию об элементе
		:return: ничего не возвращается
		'''
		print("(A,Z)= (",self.A,",",self.Z,")")
		print("Gя = ",Ca.g_energy()," МэВ")
		print("M = ",Ca.mass()," МэВ = ",Ca.mass()/931.5," а.е.м.")
		print("r = ",Ca.r()," Фм")
		print("Устойчив к бета распаду?: ",Ca.canBeta())
		print("Возможно деление на 2 одинаковых четно-четных осколка?: ",Ca.canHalf())

#производные от класса Атом функции:
def radius(А):
	'''
	Вычисление радиуса частицы
	:X:  Type is Integer. Массовое число A
	:return:  Type is float. Радиус r, Фм
	'''
	temp = Atom(А,20)
	r = temp.r()
	del temp
	return(r)

def gCa(t):
	'''
	Вычисление энергии связи частицы Ca в зависимости от изотопа с массовым числом A
	:A:  Type is Integer. Массовое число A
	:return:  Type is float. энергии связи частицы, Мэв
	'''
	return(Atom(t,20).g_energy())

def stableZ(A):
	'''
	Вычисление энергии связи частицы Ca в зависимости от изотопа с массовым числом A
	:A:  Type is Integer. Массовое число A
	:return:  Type is float. Зарядовое число Z
	'''
	Z0 = A/(0.015*np.power(A,(2/3))+1.98) #линия стабильности ядер
	return(Z0)

#применение

A = int(input("Введите A: "))
Z = int(input("Введите Z: "))
Ca = Atom(A,Z)
Ca.dataPrint()
plotf(1,10,1,radius,"массовое число A","r, Фм","зависимость r(A)","r(A)")
plotf(30,50,1,gCa,"массовое число A","G, МэВ","зaвисимость энергии связи частицы Ca от изотопа Ca c массовым числом A","G связи")
plotf(1,100,1,stableZ,"массовое число A","зарядовое число Z","линия стабильности","Z(A)")
