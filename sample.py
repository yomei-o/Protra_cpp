import PyPtsim

def main():
	sim=PyPtsim.PyPtsim()
	ret=sim.Initialize()
	if ret!=0 :
		print("PyPtsim initialize error")
		return
	sim.AddLog(2020,2,4,b"1379",b"hoge",100,20,0)
	sim.AddLog(2020,2,18,b"1379",b"hoge",100,20,1)
	ret=sim.Performance()
	if ret!=0 :
		print("PyPtsim execute error")
		return
	print("OK")

if __name__ == '__main__':
	main()
