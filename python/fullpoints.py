import sys
import math
import _pickle as p

Version = 0.1

class IdotException(Exception):
    def __init__(self, val):
        Exception.__init__(self)
        self.val = val
        return

class Learning:
    '''Learning Class Description'''
    score = 0

    def __init__(self, name):
        self.name = name
        print("create", self.name)
        return

    def __del__(self):
        print("delete", self.name)
        return

    def guess(self, n, m=5):
        '''guess doc info'''
        for i in range(1, m):
            try:
                userinput = str(input('Enter an integer : '))
                # Other work can continue as usual here
                guess = int(userinput)
                if guess == n:
                    print('Congratulations, you guessed it.')  # New block starts here
                    print("(but you do not win any prizes!)")  # New block ends here
                    break # Exit the loop
                elif i == 4:
                    raise IdotException("You such a idiot!!!")
                elif guess < n:
                    print('No, it is a little higher than that')  # Another block
                    # You can do whatever you want in a block ...
                else:
                    print('No, it is a little lower than that')
            except IdotException as e:
                print(e.val)
            except ValueError as e:
                print(e)
            else:
                print("main code execution done!!!")
            finally:
                # always execute this part
                print("finally do something!!!")
        # you must have guess > number to reach here
        print('Done')
        # This last statement is always executed, after the if statement is executed
        return

    def shopping_list(self):
        # This is my shopping list
        shoplist = ['apple', 'mango', 'carrot', 'banana']
        print('I have', len(shoplist), 'items to purchase.')
        print('These items are:')  # Notice the comma at end of the line
        for item in shoplist:
            print(item, )

        print('\nI also have to buy rice.')
        shoplist.append('rice')
        print('My shopping list is now', shoplist)

        print('I will sort my list now')
        shoplist.sort()
        print('Sorted shopping list is', shoplist)

        print('The first item I will buy is', shoplist[2])
        olditem = shoplist[2]
        del shoplist[2]
        print('I bought the', olditem)
        print('My shopping list is now', shoplist)
        return

    def tupple_example(self):
        zoo = ('wolf', 'elephant', 'penguin')
        print('Number of animals in the zoo is', len(zoo))
        new_zoo = ('monkey', 'dolphin', zoo)
        print('Number of animals in the new zoo is', len(new_zoo))
        print('All animals in new zoo are', new_zoo)
        print('Animals brought from old zoo are', new_zoo[2])
        print('Last animal brought from old zoo is %s' % (new_zoo[2][2]))
        return

    def dictionary_example(self):
        # 'ab' is short for 'a'ddress'b'ook
        ab = {'Swaroop': 'swaroopch@byteofpython.info',
              'Larry': 'larry@wall.org',
              'Matsumoto': 'matz@ruby-lang.org',
              'Spammer': 'spammer@hotmail.com'
              }
        print("Swaroop's address is %s" % ab['Swaroop'])
        # Adding a key/value pair
        ab['Guido'] = 'guido@python.org'
        # Deleting a key/value pair
        del ab['Spammer']
        print('\nThere are %d contacts in the address-book\n' % len(ab))
        for name, address in ab.items():
            print('Contact %s at %s' % (name, address))
        if 'Guido' in ab:  # OR ab.has_key('Guido')
            print("\nGuido's address is %s" % ab['Guido'])
        return

    def references(self):
        print('Simple Assignment')
        shoplist = ['apple', 'mango', 'carrot', 'banana']
        mylist = shoplist  # mylist is just another name pointing to the same object!
        del shoplist[0]  # I purchased the first item, so I remove it from the list
        print('shoplist is', shoplist)
        print('mylist is', mylist)
        # notice that both shoplist and mylist both print the same list without
        # the 'apple' confirming that they point to the same object
        print('Copy by making a full slice')
        mylist = shoplist[:]  # make a copy by doing a full slice
        del mylist[0]  # remove first item
        print('shoplist is', shoplist)
        print('mylist is', mylist)
        # notice that now the two lists are different
        return

    def strings_example(self):
        name = 'Swaroop'  # This is a string object
        if name.startswith('Swa'):
            print('Yes, the string starts with "Swa"')
        if 'a' in name:
            print('Yes, it contains the string "a"')
        if name.find('war') != -1:
            print('Yes, it contains the string "war"')
        delimiter = '_*_'
        mylist = ['Brazil', 'Russia', 'India', 'China']
        print(delimiter.join(mylist))
        return

    def writeTo(self):
        f = open("abc.txt", "wb")
        # f.write("certainest")
        slist = ["a", "b", "c"]
        p.dump(slist, f)
        f.close()
        return

    def readFrom(self):
        f = open("abc.txt", "rb")
        something = p.load(f)
        print(something)
        f.seek(0)
        while True:
            line = f.readline()
            if len(line) == 0:
                break
            print(line)
        f.close()
        return

    def powerOf(self, mylist):
        assert isinstance(mylist, list) or len(mylist) > 0
        newlist = [int(math.pow(i, 2)) for i in mylist if i > 2]
        print(newlist)
        return

    def lambda_repeat(self, n):
        return lambda s: s * n

    def strExec(self, s):
        exec(s)
        return

    def strEval(self, s):
        # the repr function or the backticks are used to
        # obtain a printable representation of the object.
        # you can control what your objects return for the
        # repr function by defining the __repr__ method in your class
        # >>>i=['item']  >>>repr(i) >>>"['item']"
        if repr(eval(s)) == str(6):
            print("eval %s = %s" % (s, eval(s)))
        return

class Test(Learning):
    def __init__(self, name):
        Learning.__init__(self, name)

    def __del__(self):
        Learning.__del__(self)

    def doTest(self):
        Learning.shopping_list(self)
        Learning.tupple_example(self)
        Learning.references(self)
        Learning.strings_example(self)
        print(Learning.__doc__)


if __name__ == '__main__':
    pass
    t = Test("MyLearning")
    t.doTest()
    #t.guess(23)
    '''print(guess.__doc__)'''
    t.writeTo()
    t.readFrom()
    t.powerOf([1,2,3,4,5])
    repeater = t.lambda_repeat(3)
    print(repeater("abc "))
    t.strExec("print('hello world')")
    t.strEval("2 * 3")
    del t

