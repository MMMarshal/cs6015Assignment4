import random
import string


def getLegalRandomPoints():
    arr = [None] * 6
    val = ""
    for i in arr:
        i = random.randint(1, 50)
        val += str(i) + ' '
    val = val[:-1]
    return val


def getLegalSquare():
    i = random.randint(1, 100)
    arr = [i] * 6
    arr[1] = arr[4] = 0
    val = ""
    for x in arr:
        val += str(x) + ' '
    val = val[:-1]
    return val


def getLegalRectangle():
    arr = [0] * 6
    i = random.randint(1, 100)
    j = random.randint(1, 100)
    while (i == j):
        j = random.randint(1, 100);
    arr[0] = arr[2] = i
    arr[3] = arr[5] = j
    val = ""
    for x in arr:
        val += str(x) + ' '
    val = val[:-1]
    return val


def getBadPoints():
    arr = [None] * 6
    val = ""
    for x in arr:
        val += str(random.randint(0, 10000)) + ' '
    val = val[:-1]
    return val


def makeBadPointsFiles(max):
    for x in range(0, max):
        f = open("coverage/BadPoints/BadPoint" + str(x), "w+")
        f.write(getBadPoints())
        f.close()


def makeRandomStringFiles(max):
    for x in range(0, max):
        f = open("coverage/RandomStrings/RandomString" + str(x), "w+")
        f.write(''.join(random.choice(string.digits + string.ascii_letters + string.punctuation + ' ') for _ in range(random.randint(1, 100))))
        f.close()


def makeLegalRandomPointsFile(max):
    for x in range(0, max):
        f = open("coverage/LegalRandomPoints/LegalRandomPoint" + str(x), "w+")
        f.write(getLegalRandomPoints())
        f.close()


def makeLegalRandonSquaresFile(max):
    for x in range(0, max):
        f = open("coverage/LegalRandomSquares/LegalRandomSquare" + str(x), "w+")
        f.write(getLegalSquare())
        f.close()


def makeLegalRandonRectanglesFile(max):
    for x in range(0, max):
        f = open("coverage/LegalRandomRectangles/LegalRandomRectangle" + str(x), "w+")
        f.write(getLegalRectangle())
        f.close()


makeBadPointsFiles(100)
makeRandomStringFiles(100)
makeLegalRandomPointsFile(2000)
makeLegalRandonSquaresFile(100)
makeLegalRandonRectanglesFile(100)
