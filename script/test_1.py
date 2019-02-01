#! /usr/bin/python3
import ctypes
import random
from threading import Thread
from multiprocessing import Pool


BYTE_SIZE = 50
MAX_UINT64 = 0xFFFFFFFFFFFFFFFF
MAX_UINT128 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF


def test_add(name):
    wrapper = ctypes.CDLL('./build/libwrapper.so')
    print('Process {} started'.format(name))

    for _ in range(MAX_UINT128):
        a = random.randrange(MAX_UINT128 + 1)
        b = random.randrange(MAX_UINT128 + 1)

        byte_a = str(a).encode('utf-8')
        byte_b = str(b).encode('utf-8')

        result_byte = ctypes.create_string_buffer(BYTE_SIZE)
        wrapper.add_uint128(byte_a, byte_b, result_byte, BYTE_SIZE)

        expected_int = (a + b) % (MAX_UINT128 + 1)
        result_int = int(result_byte.value.decode('utf-8'), base=16)
        if result_int != expected_int:
            print('0x{:x} - [a]'.format(a))
            print('0x{:x} - [b]'.format(b))
            print('0x{:x} - [result]'.format(result_int))
            print('0x{:x} - [expect]'.format(expected_int))
            print('0x{:x} - [error]'.format(expected_int - result_int))
            break


def test_sub(name):
    wrapper = ctypes.CDLL('./build/libwrapper.so')
    print('Process {} started'.format(name))

    for _ in range(MAX_UINT128):
        a = random.randrange(MAX_UINT128 + 1)
        b = random.randrange(MAX_UINT128 + 1)

        byte_a = str(a).encode('utf-8')
        byte_b = str(b).encode('utf-8')

        result_byte = ctypes.create_string_buffer(BYTE_SIZE)
        wrapper.sub_uint128(byte_a, byte_b, result_byte, BYTE_SIZE)

        expected_int = (a - b) % (MAX_UINT128 + 1)
        result_int = int(result_byte.value.decode('utf-8'), base=16)
        if result_int != expected_int:
            print('{:x} - [a]'.format(a))
            print('{:x} - [b]'.format(b))
            print('{:x} - [result]'.format(result_int))
            print('{:x} - [expect]'.format(expected_int))
            print('{:x} - [error]'.format(expected_int - result_int))
            break


def runner(x):
        p1 = Thread(target=test_add, args=(x,))
        p2 = Thread(target=test_sub, args=(x,))
        p1.start()
        p2.start()
        p1.join()
        p2.join()


def main():
    with Pool(8) as p:
        p.map(runner, range(16))


if __name__ == "__main__":
    pass
    # test_sub(1)
    # main()
