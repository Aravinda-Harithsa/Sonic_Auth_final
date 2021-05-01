psk = {
'0'   :"10110111",
'1'   :"10111101",

}

decode_psk = {}
for k, v in psk.items():
    decode_psk[v] = k

def encode(string):
    result = []
    for c in string:
        result.append(psk[c])
    return '00'.join(result) + '00'

def decode(string):
    try:
        return decode_psk[''.join([str(i) for i in string])]
    except:
        return ''
