import json
import subprocess
import os

def saveFileToTemp(folder_path,file_name,file_content,dtype="text"):
	try:
		if dtype == "text":
			with open(folder_path+file_name,"a") as f:
				f.write(file_content)
		elif dtype == "json":
			with open(folder_path+file_name,"a") as f:
				json.dump(file_content,f)
				
		return True
	except:
		return False
			
def saveTempFile(folder_path):
	try:
		with open("./tools/temp/EtherGame.lna","r") as f:
			with open(folder_path+"EtherGame.lna","a") as fs:
				fs.write(f.read())
		with open("./tools/temp/blindAuction.ast","r") as f:
			with open(folder_path+"blindAuction.ast","a") as fs:
				fs.write(f.read())
				
		with open("./tools/temp/etherGame.json","r") as f:
			with open(folder_path+"etherGame.json","a") as fs:
				json.dump(json.load(f),fs)
				
		return True
	except:
		return False
		
def unfolding(folder_path,lna_name,context_name,context_type,ltl_name,sol_ast_name,lna_json_name,initial_marking):
	lna_PATH = folder_path + lna_name
	context_PATH = folder_path + context_name
	ltl_PATH = folder_path + ltl_name
	sol_ast_PATH = folder_path + sol_ast_name
	lna_json_PATH = folder_path + lna_json_name
	initial_marking_PATH = folder_path + initial_marking
	
	output_PATH = folder_path
	output_NAME = lna_name.split(".")[0] + "_HCPN"
	
	command = "./tools/tools/unfolding" + " --lna " + lna_PATH + " --context " + context_PATH + " --context-type " + context_type + \
		  " --ltl " + ltl_PATH + " --sol-ast " + sol_ast_PATH + " --lna-json " + lna_json_PATH + " --im-json " + initial_marking_PATH + \
		  " --output_path " + output_PATH + " --output_name " + output_NAME
	
	pathT = "./"
	
	output = subprocess.run(command, cwd=pathT, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	
	return {"err":output.stderr.decode(),"file_path":output_PATH,"file_name":output_NAME}
	
def helenaCheck(folder_path,hcpn_name,prop_name):
	hcpn_PATH = folder_path + hcpn_name
	prop_PATH = folder_path + prop_name
	
	prop_content = ""
	with open(prop_PATH, "r") as f:
		prop_content = f.read()
	
	begin = prop_content.find("property") + 9
	end = prop_content.find(":")
	
	property_name = prop_content[begin:end]
		
	command = "helena -N=CHECK-" + property_name + " -p=" + prop_PATH + " " + hcpn_PATH

	pathT = "./"
	
	output = subprocess.run(command, cwd=pathT, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

	return {"err":output.stderr.decode(),"output":output.stdout.decode()}

def removeFolder(full_path):
	try:
		if os.path.exists(full_path):
			list_dir = os.listdir(full_path)
			if len(list_dir) > 0:
				for file_path in list_dir:
					os.remove(full_path+file_path)
			os.rmdir(full_path)
		else:	
			pass
	except:
		pass
