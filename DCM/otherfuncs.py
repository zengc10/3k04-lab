from tkinter import messagebox

def clearFrame(frame):
    try:
        for i in frame.winfo_children():
            i.destroy()
    except:
        print('**CLEARFRAME ERROR')

def checkEmptyCredentials(username, password):
    if username == '' or password == '':
        return True

def getParamVals(parameters):
    for i in parameters:
        p = parameters[i]
        if p != None:
            cur = p["Spinbox"].get()
            if float(cur) >= p["Range"][0] and float(cur) <= p["Range"][1]:
                p["Values"] = p["Spinbox"].get()
            else:
                messagebox.showwarning("Parameter Editor", "Invalid Value for {}".format(p["Name"]))
                p["Values"] = None