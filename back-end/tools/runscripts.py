import json
import requests
import subprocess
from subprocess import Popen, PIPE, STDOUT


# for Windows
path = r"C:\Users\Admin\Desktop\SmartContractChecking-Application-hadt\tools"

# for Ubuntu
path = "/home/meedee/Desktop/project/ducdm/SmartContractChecking-Application/tools"


# ---save file to temporary----
# data = {'name':'', '':'', ...}
def savetotemporary(data):
    for k in data.keys():
        if k == 'name':
            continue
        with open(f'{path}/temporary/{k}', 'w') as f:
            f.write(data[k])

data = {
    "name": "getdata",
    "context_PATH.xml":"<DCRModel>\n    <id>220802</id>\n    <title>Healthcare Workflow</title>\n    <events>\n        <id>play</id>\n    </events>\n    <events>\n        <id>claimReward</id>\n    </events>\n    \n    <rules>\n        <type>condition</type>\n        <source>play</source>\n        <target>claimReward</target>\n    </rules>\n    <rules>\n        <type>include</type>\n        <source>claimReward</source>\n        <target>play</target>\n    </rules>\n</DCRModel>",
    "ltl_PATH.json": "{\n    \"type\": \"general\",\n    \"params\": {\n        \"name\": \"under_over_flow\",\n        \"inputs\": [\"currentBalance\"]\n    }\n}"
}
savetotemporary(data=data)


def unfolding():
    # get from temporary
    # context_PATH = './test/test.xml'
    # ltl_PATH = './test/ltl.json'
    context_PATH = '../temporary/context_PATH.xml'
    ltl_PATH = '../temporary/ltl_PATH.json'

    # wait tools
    lna_PATH = './test/EtherGame.lna'
    sol_ast_PATH = './test/blindAuction.ast'
    lna_json_PATH = './test/etherGame.json'

    # output
    output_PATH = './output/'
    output_NAME = 'test'

    commandUnf = "./main --lna " + lna_PATH + " --context " + context_PATH + " --ltl "+ltl_PATH+" --sol-ast " + \
        sol_ast_PATH+" --lna-json "+lna_json_PATH+" --output_path " + \
        output_PATH+" --output_name "+output_NAME
    # print (commandUnf)
    pathUnf = path + r"/unfolding"
    unfolding = subprocess.run(
        commandUnf, cwd=pathUnf, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
unfolding()

def runHelena():
    helenaPath = path + r"/unfolding/output"
    helenaFile = "test.lna"
    propfile = helenaPath + "/" + helenaFile[0:-4]+".prop.lna"
    f = open(propfile, 'r')
    propLna = str(f.read())
    begin = propLna.find("property ")+9
    end = propLna.find(":")
    property = propLna[begin:end]
    # print(property)
    helena = "helena -N=CHECK -p=" + property + " " + helenaFile
    pro4 = subprocess.run(helena, cwd=helenaPath, shell=True,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output = str(pro4.stdout.decode("cp932"))
    start = output.find("Helena report")
    report = output[start:]
    # print(repr(report))
    f.close()
    return report

runHelena()