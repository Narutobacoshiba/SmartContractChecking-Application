#fixed code for lna.
class FixedLNACode():
	def __init__(self, event_num):
		self.num = event_num
		
	def getDefaultType(self):
		code = "\n\ttype bools: range 0 .. 1;" +\
		       "\n\ttype count: range 0 .. "+str(self.num)+";"+\
		       "\n\tsubtype event_id: count range 0 .. "+str(self.num-1)+";"+\
		       "\n\ttype marking_value: list [event_id] of bools with capacity "+str(self.num)+";"+\
		       "\n\ttype mvalue: struct {event_id id; bools vl;};"+\
		       "\n\ttype vchange: list [event_id] of mvalue with capacity "+str(self.num)+";"+\
		       "\n\ttype cvalue: struct {bools cv1; bools cv2;};"+\
		       "\n\ttype vcondition: list [event_id] of cvalue with capacity "+str(self.num)+";"
		return code
		
	def getAsType(self):
		code = "\n\ttype as_type: struct {event_id state; bools value;};"
		return code
	
	def getAsPlace(self):
		code = "\n\tplace accepting_state{"+\
		       "\n\t\tdom: as_type;"+\
		       "\n\t\tinit: <({0,0})>;"+\
		       "\n\t}"
		return code
	
	def getMarkingPlace(self):
		code = "\n\tplace marking{"+\
		       "\n\t\tdom: marking_value*marking_value*marking_value;"+\
		       "\n\t\tinit: <(|"+",".join(["1" for i in range(self.num)])+"|,|"+",".join(["0" for i in range(self.num)])+"|,|"+",".join(["0" for i in range(self.num)])+"|)>;"+\
		       "\n\t}"
		return code
	
	def getDefaultFunctions(self):
		code = "\n\tfunction cvalue(marking_value mv, vchange lc) -> marking_value{"+\
			"\n\t\tmarking_value m := empty;"+\
			"\n\t\tfor(v in mv){"+\
			"\n\t\t\tm := m & v;"+\
			"\n\t\t}"+\
			"\n\t\tfor(v in lc){"+\
			"\n\t\t\tm[v.id] := v.vl;"+\
			"\n\t\t}"+\
			"\n\t\treturn m;"+\
			"\n\t}"+\
			"\n\tfunction confirm_condition(vcondition vc) -> bools{"+\
			"\n\t\tbools ret := 1;"+\
			"\n\t\tfor(v in vc){"+\
			"\n\t\t\tif(v.cv1 = 1 and v.cv2 = 0) ret := 0;"+\
			"\n\t\t}"+\
			"\n\t\treturn ret;"+\
			"\n\t}"+\
			"\n\tfunction confirm_milestone(vcondition vc) -> bools{"+\
			"\n\t\tbools ret := 1;"+\
			"\n\t\tfor(v in vc){"+\
			"\n\t\t\tif(v.cv1 = 1 and v.cv2 = 1) ret := 0;"+\
			"\n\t\t}"+\
			"\n\t\treturn ret;"+\
			"\n\t}"
		return code	
	
	def getResExFunction(self):
		code = "\n\tfunction response_exists(marking_value m) -> bool {"+\
			"\n\t\tfor(v in m){"+\
			"\n\t\t\tif(v = 1) return true;"+\
			"\n\t\t}"+\
			"\n\t\treturn false;"+\
			"\n\t}"
		return code
	
	def getCalAsFunction(self):
		excode = "|"+",".join(["0" for i in range(self.num)])+"|"
		code = "\n\tfunction calculate_accepting_state(as_type ast,event_id cid,marking_value current_include, marking_value current_response, marking_value next_include, marking_value next_response) -> as_type {"+\
			"\n\t\tmarking_value include_response_current := "+excode+";"+\
			"\n\t\tmarking_value include_response_next := "+excode+";"+\
			"\n\t\tmarking_value acceptable_set := "+excode+";"+\
			"\n\t\tmarking_value m_set := "+excode+";"+\
			"\n\t\tcount min_m_set := "+str(self.num)+";"+\
			"\n\t\tcount min_include_response_current := "+str(self.num)+";"+\
			"\n\t\tcount index := "+str(self.num)+";"+\
			"\n\t\tcount m_set_count := 0;"+\
			"\n\t\tcount include_response_current_set_count := 0;"+\
			"\n\t\tcount include_response_next_set_count := 0;"+\
			"\n\t\tbools ret_value := 0;"+\
			"\n\t\tevent_id ret_state := ast.state;"+\
			"\n\t\tfor(idx in event_id){"+\
			"\n\t\t\tif(current_include[idx] = 1 and current_response[idx] = 1) include_response_current[idx] := 1;"+\
			"\n\t\t\tif(next_include[idx] = 1 and next_response[idx] = 1) include_response_next[idx] := 1;"+\
			"\n\t\t\tif(idx > ast.state and include_response_current[idx] = 1) m_set[idx] := 1;"+\
			"\n\t\t\tif(include_response_current[idx] = 1 and include_response_next[idx] = 0) acceptable_set[idx] := 1;"+\
			"\n\t\t}"+\
			"\n\t\tacceptable_set[cid] := 1;"+\
			"\n\t\twhile(index > 0){"+\
			"\n\t\t\tif(m_set[index-1] = 1){"+\
			"\n\t\t\t\tmin_m_set := (index-1);"+\
			"\n\t\t\t\tm_set_count := (m_set_count+1);"+\
			"\n\t\t\t}"+\
			"\n\t\t\tif(include_response_current[index-1] = 1){"+\
			"\n\t\t\t\tmin_include_response_current := (index-1);"+\
			"\n\t\t\t\tinclude_response_current_set_count := (include_response_current_set_count+1);"+\
			"\n\t\t\t}" +\
			"\n\t\t\tif(include_response_next[index-1] = 1) include_response_next_set_count := (include_response_next_set_count+1);"+\
			"\n\t\t\t\tindex := (index-1);"+\
			"\n\t\t}"+\
			"\n\t\tif(include_response_next_set_count = 0) ret_value := 1;"+\
			"\n\t\tif((m_set_count>0) and (acceptable_set[min_m_set]=1)){"+\
			"\n\t\t\tret_value := 1;"+\
			"\n\t\t\tret_state := min_m_set;"+\
			"\n\t\t}"+\
			"\n\t\tif((m_set_count=0) and (min_include_response_current<4)and(acceptable_set[min_include_response_current]=1)){"+\
			"\n\t\t\tret_value := 1;"+\
			"\n\t\t\tret_state := min_include_response_current;"+\
			"\n\t\t}"+\
			"\n\t\treturn {ret_state,ret_value};"+\
			"\n\t}"
		return code
	
	def getLivenessProp(self):
		code = "\n\tproposition is_accepting_state:"+\
			"\n\t\texists (p in accepting_state | p->1.value = 1);"
		return code
		
	def getDeadlockFreeProp(self):
		code = "\n\tproposition deadlock_free:"+\
			"\n\t\texists (v in marking | response_exists(v->3)) = false;"
		return code

#fixed code for property
class LNAProperty():
	def __init__(self):
		pass
	
	def getLivenessProperty(self):
		code = "ltl property prop:"+\
			"\n\t[] (<> is_accepting_state);"
		return code
	
	def getDeadlockProperty(self):
		code = "state property prop:"+\
			"\n\treject deadlock;"+\
			"\n\taccept deadlock_free;"
		return code	

#Lna transition class
class LNATransition():
	def __init__(self, event_name, event_id, relations, trans_type = 'd'):
		"""
			:event_name: string
			:event_id: int
			:relation: dict({"condition":[],"include":[],"milestone":[],"exclude":[],"response":[]})
			:trans_type: {'d','l'} -> 'd': deadlock, 'l': liveness
		"""
		self.event_name = event_name
		self.event_id = event_id
		self.relations = relations
		self.trans_type = trans_type
			
	def getInArcs(self):
		"""
			create in arcs for transition:
			example output: in {
									marking: <(include,execute,response)>;
								}
		"""
		code = ""
		if self.trans_type == 'l':
			code = "\n\t\tin {"+\
				"\n\t\t\taccepting_state: <(ast)>;"+\
				"\n\t\t\tmarking: <(include,execute,response)>;"+\
			  	"\n\t\t}"
		elif self.trans_type == 'd':
			code = "\n\t\tin {"+\
				"\n\t\t\tmarking: <(include,execute,response)>;"+\
			  	"\n\t\t}"
			
		return code
	
	def getOutArcs(self):
		"""
			create out arcs for transition:
			example output: out {
									marking: <(include,cvalue(execute,|{1,1}|),cvalue(response,|{1,0}|))>;
								}

			default arc: marking;
			if trans_type = 'l': add arc accepting_state

			params in  <()> is determined by "include","exclude","response" relation
		"""

		as_arcs = ""
		marking_params = []
		
		incl_params = []
		for incl_event in self.relations["include"]:
			incl_params.append("{"+str(incl_event)+",1}")
		for excl_event in self.relations["exclude"]:
			incl_params.append("{"+str(excl_event)+",1}")
		if len(incl_params) > 0:
			marking_params.append("cvalue(include,|"+",".join(incl_params)+"|)")
		else:
			marking_params.append("include")
		
		marking_params.append("cvalue(execute,|{"+str(self.event_id)+",1}|)")
		
		resp_params = []
		for resp_event in self.relations["response"]:
			resp_params.append("{"+str(resp_event)+",1}")
		if self.event_id not in self.relations["response"]:
			resp_params.append("{"+str(self.event_id)+",0}")
		marking_params.append("cvalue(response,|"+",".join(resp_params)+"|)")
		
		if self.trans_type == "l":
			as_params = ["ast",str(self.event_id),"include","response",marking_params[0],marking_params[2]]
			as_arcs = "calculate_accepting_state("+",".join(as_params)+")"
		
		code = ""
		if as_arcs != "":
			code = "\n\t\tout {" +\
				"\n\t\t\taccepting_state: <("+as_arcs+")>;"+\
				"\n\t\t\tmarking: <("+",".join(marking_params)+")>;" +\
		    		"\n\t\t}"
		else:
			code = "\n\t\tout {" +\
				"\n\t\t\tmarking: <("+",".join(marking_params)+")>;" +\
		    		"\n\t\t}"
		return code
	
	def getGuard(self, level="n"):
		"""
			create guard for transition
			example output: gurad: (include[0] = 1) and (confirm_condition(|{include[1],execute[1]}|) = 1);
			type of condition for guard: "include", "response", "confirm_condition()", "confirm_milestone()"
		"""
		guard_params = []
		
		guard_params.append("(include["+str(self.event_id)+"] = 1)")
		if level == "s":
			guard_params.append("(response["+str(self.event_id)+"] = 1)")
		
		cond_params = []
		for cond_event in self.relations["condition"]:
			 cond_params.append("{include["+str(cond_event)+"],execute["+str(cond_event)+"]}")
		
		miles_params = []
		for miles_event in self.relations["milestone"]:
			 miles_params.append("{include["+str(cond_event)+"],execute["+str(cond_event)+"]}")
		
		if len(cond_params) > 0:
			guard_params.append("(confirm_condition(|"+",".join(cond_params)+"|) = 1)")
		
		if len(miles_params) > 0:
			guard_params.append("(confirm_milestone(|"+",".join(miles_params)+"|) = 1)")
		
		code = "\n\t\tguard: "+" and ".join(guard_params)+";"
		return code
	
	def getPriority(self):
		"""
			create priority for transition
		"""
		code = "\n\t\tpriority: (response["+str(self.event_id)+"] = 1 or execute["+str(self.event_id)+"] = 0) ? 1 : 0;"
		return code
		
	def getAllCode(self):
		"""
			create full code for strongly and normal guard (strongly for strongly deadlock and strongly liveness)
		"""
		in_arcs = self.getInArcs()
		out_arcs = self.getOutArcs()
		normal_guard = self.getGuard("n")
		strong_guard = self.getGuard("s")
		priority = self.getPriority()
		
		if self.trans_type == "d":
			norm_code = "\n\ttransition "+self.event_name+"{" +in_arcs+out_arcs+normal_guard+"\n\t}"
			strong_code = "\n\ttransition "+self.event_name+"{" +in_arcs+out_arcs+strong_guard+"\n\t}"

		elif self.trans_type == "l":
			norm_code = "\n\ttransition "+self.event_name+"{" +in_arcs+out_arcs+normal_guard+priority+"\n\t}"
			strong_code = "\n\ttransition "+self.event_name+"{" +in_arcs+out_arcs+strong_guard+priority+"\n\t}"

		return norm_code, strong_code	
		
class Translator():
	def __init__(self, dcrClass):
		self.name = dcrClass.getName()
		self.events = dcrClass.getEvents()
		self.ERE = dcrClass.getERE()
		self.num_events = len(self.events)
		
	def translate(self):
		fixed_code = FixedLNACode(self.num_events)
		events_id, events_relations = self.analyseERE(self.events,self.ERE)
		
		deadlock_code,stdeadlock_code = self.createDeadlockCode(fixed_code,events_id,events_relations)
		
		liveness_code,stliveness_code = self.createLivenessCode(fixed_code,events_id,events_relations)
		
		return deadlock_code,stdeadlock_code,liveness_code,stliveness_code
		
	def analyseERE(self,events,ere):
		"""
			input:
				:events: list(string) ["event1","event2","event3"]
				:ere: list(dict) [{"_eventsource":"event1","_eventdest":"event2","relations":["condition","include"]}]
			
			output:
				events_id: dict {"event1":0,"event2":1,"event3":2}
				events_relations: dict {0:{"include": [1],"exclude": [],"response": [],"condition": [],"milestone": []},
										1:{"include": [],"exclude": [],"response": [],"condition": [0],"milestone": []}
										2:{"include": [],"exclude": [],"response": [],"condition": [],"milestone": []}}
			
		"""
		events_id = {events[idx]:idx for idx in range(self.num_events)}
		events_relations = {idx:{"include": [],"exclude": [],"response": [],
					 "condition": [],"milestone": []} for idx in range(self.num_events)}
		
		for element in ere:
			event_source = element["_eventsource"]
			event_dest = element["_eventdest"]
			relations = element["relations"]
			
			for rel in relations:
				if rel == "condition":
					events_relations[events_id[event_dest]]["condition"].append(events_id[event_source])
				if rel == "milestone":
					events_relations[events_id[event_dest]]["milestone"].append(events_id[event_source])
				if rel == "include":
					events_relations[events_id[event_source]]["include"].append(events_id[event_dest])
				if rel == "exclude":
					events_relations[events_id[event_source]]["exclude"].append(events_id[event_dest])
				if rel == "response":
					events_relations[events_id[event_source]]["response"].append(events_id[event_dest])	
		return events_id, events_relations
	
	def createDeadlockCode(self, fixed_code, events_id, events_relations):
		"""
			create code for deadlock detection
		"""
		dtype = fixed_code.getDefaultType()
		mplace = fixed_code.getMarkingPlace()
		dfunc = fixed_code.getDefaultFunctions()
		rfunc = fixed_code.getResExFunction()
		prop = fixed_code.getDeadlockFreeProp()
		
		norm_trans = []
		st_trans = []
		
		for key,value in events_id.items():
			no_code, st_code = LNATransition(key,value,events_relations[value],'d').getAllCode()
			norm_trans.append(no_code)
			st_trans.append(st_code)
		
		norm_trans_code = "\n".join(norm_trans)
		st_trans_code = "\n".join(st_trans)
		
		upper_code = self.name+"{" +\
			     "\n\n\t/* ------- define type ------- */" +\
			     dtype +\
			     "\n\n\t/* ------- define place ------- */" +\
			     mplace +\
			     "\n\n\t/* ------- define function ------- */" +\
			     dfunc + "\n" + rfunc +\
			     "\n\n\t/* ------- define transition ------- */" 
		lower_code = "\n\n\t/* ------- define proposition ------- */"+prop+"\n\n}"
		
		normal_deadlock_code = upper_code+norm_trans_code+lower_code
		strong_deadlock_code = upper_code+st_trans_code+lower_code
		
		return normal_deadlock_code,strong_deadlock_code
		
	def createLivenessCode(self, fixed_code, events_id, events_relations):
		"""
			create code for liveness verification
		"""
		dtype = fixed_code.getDefaultType()
		atype = fixed_code.getAsType()
		mplace = fixed_code.getMarkingPlace()
		aplace = fixed_code.getAsPlace()
		dfunc = fixed_code.getDefaultFunctions()
		cafunc = fixed_code.getCalAsFunction()
		prop = fixed_code.getLivenessProp()
		
		norm_trans = []
		st_trans = []
		
		for key,value in events_id.items():
			no_code, st_code = LNATransition(key,value,events_relations[value],'l').getAllCode()
			norm_trans.append(no_code)
			st_trans.append(st_code)
		
		norm_trans_code = "\n".join(norm_trans)
		st_trans_code = "\n".join(st_trans)
		
		upper_code = self.name+"{" +\
			     "\n\n\t/* ------- define type ------- */" +\
			     dtype + atype +\
			     "\n\n\t/* ------- define place ------- */" +\
			     mplace + aplace +\
			     "\n\n\t/* ------- define function ------- */" +\
			     dfunc + "\n" + cafunc +\
			     "\n\n\t/* ------- define transition ------- */" 
		lower_code = "\n\n\t/* ------- define proposition ------- */"+prop+"\n\n}"
		
		normal_liveness_code = upper_code+norm_trans_code+lower_code
		strong_liveness_code = upper_code+st_trans_code+lower_code
		
		return normal_liveness_code,strong_liveness_code	
		
class DCRExample:
    def __init__(self):
        pass
    
    def getName(self):
        return "test"

    def getEvents(self):
        return ["PrescribeMedicine","Sign","GiveMedicine","DontTrust"]

    def getERE(self):
        relation = [
            {"_eventsource":"PrescribeMedicine","relations":["condition"],"_eventdest":"Sign"},
            {"_eventsource":"PrescribeMedicine","relations":["condition","response"],"_eventdest":"GiveMedicine"},

            {"_eventsource":"Sign","relations":["condition","include"],"_eventdest":"GiveMedicine"},
            {"_eventsource":"Sign","relations":["condition","include"],"_eventdest":"DontTrust"},
            
            {"_eventsource":"DontTrust","relations":["response"],"_eventdest":"Sign"},
            {"_eventsource":"GiveMedicine","relations":["exclude"],"_eventdest":"DontTrust"},
        ]

        return relation

prop = LNAProperty()
dcr_ex = DCRExample()
translator = Translator(dcr_ex)
code1,code2,code3,code4 = translator.translate()

with open("./deadlock.lna","w") as f:
	f.write(code1)
with open("./stdeadlock.lna","w") as f:
	f.write(code2)
with open("./liveness.lna","w") as f:
	f.write(code3)
with open("./stliveness.lna","w") as f:
	f.write(code4)
with open("./deadlock.prop.lna","w") as f:
	f.write(prop.getDeadlockProperty())
with open("./liveness.prop.lna","w") as f:
	f.write(prop.getLivenessProperty())
with open("./stdeadlock.prop.lna","w") as f:
	f.write(prop.getDeadlockProperty())
with open("./stliveness.prop.lna","w") as f:
	f.write(prop.getLivenessProperty())
"""helena commnad
helena -N=CHECK-prop deadlock.lna
"""
		
		
