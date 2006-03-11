#include "SDLWindow.hh"
#include "SDLEventManager.hh"

namespace RAGE
{
    namespace SDL
    {
        static const unsigned char defaulticon[] = {
	'\x42','\x4d','\x36','\x0c','\x00','\x00','\x00','\x00','\x00','\x00','\x36','\x00','\x00','\x00','\x28','\x00','\x00','\x00','\x20','\x00',
	'\x00','\x00','\x20','\x00','\x00','\x00','\x01','\x00','\x18','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x75','\x0a',
	'\x00','\x00','\x75','\x0a','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x40','\x20','\x20','\x40','\x20','\x20',
	'\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20',
	'\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x48','\x24','\x28','\x58','\x2c','\x28','\x50','\x28','\x28','\x48','\x24','\x28','\x40',
	'\x20','\x20','\x48','\x24','\x28','\x58','\x2c','\x30','\x60','\x34','\x30','\x68','\x34','\x30','\x60','\x30','\x30','\x48','\x24','\x28',
	'\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20',
	'\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x50','\x2c','\x28','\x50','\x2c','\x30','\x50','\x2c','\x28','\x48',
	'\x24','\x28','\x48','\x20','\x20','\x40','\x20','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x58','\x34','\x30',
	'\x60','\x34','\x30','\x58','\x30','\x30','\x58','\x30','\x30','\x58','\x2c','\x28','\x58','\x2c','\x28','\x58','\x2c','\x28','\x60','\x34',
	'\x30','\x58','\x30','\x30','\x60','\x34','\x38','\x60','\x34','\x30','\x80','\x4c','\x48','\x78','\x40','\x40','\x68','\x34','\x30','\x50',
	'\x24','\x28','\x40','\x1c','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20',
	'\x40','\x20','\x20','\x40','\x20','\x20','\x50','\x2c','\x28','\x48','\x24','\x28','\x40','\x20','\x20','\x48','\x24','\x20','\x50','\x28',
	'\x28','\x50','\x2c','\x28','\x50','\x2c','\x28','\x50','\x28','\x28','\x50','\x28','\x28','\x50','\x28','\x28','\x60','\x30','\x30','\x70',
	'\x40','\x40','\x90','\x58','\x50','\x90','\x5c','\x58','\x78','\x44','\x40','\x80','\x48','\x40','\x80','\x4c','\x48','\x78','\x44','\x40',
	'\x78','\x44','\x40','\x70','\x40','\x40','\x60','\x38','\x38','\x78','\x44','\x40','\x78','\x48','\x48','\x60','\x34','\x38','\x40','\x20',
	'\x20','\x40','\x1c','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40',
	'\x20','\x20','\x40','\x20','\x20','\x50','\x28','\x28','\x50','\x2c','\x30','\x50','\x28','\x28','\x48','\x20','\x20','\x58','\x30','\x30',
	'\x58','\x2c','\x28','\x50','\x28','\x28','\x60','\x30','\x30','\x60','\x34','\x30','\x68','\x38','\x38','\x68','\x38','\x38','\x68','\x38',
	'\x38','\x80','\x44','\x40','\x90','\x54','\x50','\x90','\x54','\x50','\x88','\x4c','\x48','\x88','\x50','\x50','\x90','\x58','\x50','\x90',
	'\x5c','\x58','\x88','\x58','\x50','\x78','\x48','\x40','\x70','\x3c','\x38','\x70','\x44','\x40','\x68','\x40','\x40','\x58','\x2c','\x30',
	'\x48','\x24','\x28','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20',
	'\x20','\x40','\x20','\x20','\x40','\x1c','\x20','\x48','\x20','\x20','\x48','\x24','\x28','\x68','\x40','\x40','\x90','\x60','\x58','\x90',
	'\x5c','\x58','\x88','\x54','\x50','\x80','\x4c','\x48','\x68','\x38','\x38','\x60','\x30','\x30','\x58','\x30','\x30','\x70','\x3c','\x38',
	'\x80','\x44','\x40','\x88','\x48','\x48','\x88','\x48','\x48','\x80','\x44','\x40','\x70','\x3c','\x40','\x70','\x3c','\x38','\x80','\x4c',
	'\x48','\x90','\x5c','\x58','\x90','\x58','\x58','\x60','\x34','\x30','\x48','\x24','\x28','\x40','\x1c','\x20','\x40','\x1c','\x20','\x40',
	'\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x1c','\x20','\x40','\x20','\x20','\x40','\x1c','\x18','\x38','\x14','\x18',
	'\x38','\x18','\x18','\x40','\x1c','\x20','\x50','\x20','\x20','\x50','\x24','\x28','\x60','\x34','\x30','\x68','\x34','\x38','\x68','\x34',
	'\x30','\x68','\x30','\x30','\x68','\x34','\x30','\x70','\x34','\x30','\x68','\x34','\x30','\x70','\x34','\x30','\x78','\x38','\x38','\x80',
	'\x40','\x38','\x88','\x4c','\x48','\x90','\x54','\x50','\x98','\x54','\x50','\xa0','\x50','\x48','\xa0','\x4c','\x48','\xa0','\x50','\x48',
	'\x90','\x50','\x48','\x80','\x44','\x40','\x68','\x34','\x30','\x50','\x28','\x28','\x48','\x1c','\x20','\x40','\x1c','\x18','\x38','\x18',
	'\x18','\x48','\x20','\x20','\x58','\x28','\x28','\x60','\x2c','\x28','\x48','\x24','\x20','\x48','\x20','\x20','\x50','\x28','\x28','\x50',
	'\x24','\x28','\x50','\x2c','\x28','\x88','\x48','\x40','\x48','\x20','\x20','\x50','\x28','\x28','\x40','\x20','\x20','\x68','\x34','\x30',
	'\x58','\x2c','\x30','\x60','\x34','\x30','\x60','\x2c','\x30','\x70','\x3c','\x38','\x68','\x3c','\x30','\x68','\x38','\x38','\x70','\x38',
	'\x38','\x60','\x30','\x30','\x60','\x34','\x30','\x68','\x38','\x38','\x68','\x38','\x38','\x68','\x38','\x38','\x80','\x44','\x40','\x88',
	'\x54','\x50','\x88','\x4c','\x48','\xa8','\x58','\x58','\x90','\x48','\x48','\x68','\x38','\x38','\x70','\x40','\x38','\x40','\x1c','\x20',
	'\x40','\x1c','\x20','\x38','\x18','\x18','\x70','\x34','\x30','\xa0','\x4c','\x48','\xb0','\x5c','\x50','\xd0','\x68','\x60','\xa0','\x58',
	'\x50','\xa0','\x50','\x48','\xc0','\x64','\x58','\xc0','\x64','\x58','\x80','\x48','\x40','\xb8','\x58','\x50','\x88','\x40','\x38','\xc0',
	'\x64','\x58','\xa8','\x58','\x50','\xb8','\x60','\x58','\xc8','\x68','\x60','\x98','\x54','\x48','\xa8','\x5c','\x50','\xc8','\x68','\x60',
	'\xb0','\x60','\x58','\xa8','\x5c','\x50','\xc8','\x64','\x58','\xa8','\x50','\x48','\xa0','\x50','\x48','\xc0','\x60','\x50','\x50','\x28',
	'\x28','\xa0','\x4c','\x40','\x90','\x4c','\x40','\xc0','\x68','\x60','\xc0','\x64','\x58','\xd0','\x6c','\x60','\xb8','\x64','\x58','\x68',
	'\x38','\x30','\x78','\x38','\x38','\x50','\x30','\x28','\x48','\x28','\x28','\x28','\x14','\x18','\x30','\x18','\x18','\x48','\x24','\x28',
	'\x58','\x34','\x30','\x80','\x48','\x40','\x58','\x34','\x30','\x78','\x40','\x38','\x78','\x44','\x40','\x70','\x3c','\x38','\x60','\x34',
	'\x30','\x60','\x38','\x38','\x70','\x48','\x48','\x88','\x54','\x50','\xa0','\x60','\x58','\xb0','\x64','\x58','\xb8','\x68','\x60','\xa8',
	'\x7c','\x78','\xc8','\x7c','\x78','\xd8','\x84','\x78','\xc0','\x80','\x78','\xa8','\x70','\x68','\x70','\x40','\x40','\x80','\x48','\x40',
	'\x28','\x10','\x10','\x38','\x1c','\x18','\x30','\x18','\x18','\x40','\x28','\x28','\x60','\x38','\x38','\x68','\x34','\x30','\x48','\x1c',
	'\x18','\xb0','\x34','\x40','\xb0','\x34','\x38','\xb0','\x38','\x40','\xa8','\x34','\x40','\xa8','\x34','\x40','\xa8','\x34','\x38','\xb0',
	'\x38','\x38','\xb0','\x38','\x38','\xb8','\x38','\x40','\xb8','\x3c','\x40','\xb8','\x3c','\x40','\xc0','\x3c','\x48','\xc0','\x40','\x48',
	'\xc0','\x40','\x48','\xc0','\x40','\x48','\xb8','\x3c','\x48','\xb8','\x3c','\x40','\xb8','\x38','\x38','\xb0','\x30','\x38','\xb0','\x30',
	'\x30','\xb0','\x30','\x38','\xb8','\x34','\x38','\xc0','\x3c','\x40','\xc8','\x40','\x48','\xc8','\x44','\x48','\xc8','\x40','\x48','\xc0',
	'\x3c','\x40','\xb0','\x30','\x30','\xa8','\x2c','\x30','\xa8','\x30','\x38','\x98','\x30','\x30','\x40','\x18','\x18','\x38','\x14','\x18',
	'\x68','\x30','\x20','\xa0','\x5c','\x30','\xb8','\x6c','\x40','\xb8','\x70','\x40','\x88','\x60','\x30','\x38','\x1c','\x18','\x40','\x1c',
	'\x20','\x90','\x50','\x50','\xb8','\x60','\x50','\x98','\x58','\x40','\x90','\x5c','\x40','\x90','\x60','\x48','\x98','\x64','\x48','\x98',
	'\x68','\x50','\x98','\x64','\x50','\x88','\x58','\x50','\x80','\x4c','\x50','\xc0','\x84','\x80','\xd0','\x94','\x90','\xa8','\x68','\x68',
	'\x80','\x4c','\x40','\x80','\x68','\x50','\x80','\x68','\x50','\x88','\x74','\x60','\x98','\x84','\x70','\xa0','\x8c','\x70','\x90','\x80',
	'\x68','\x78','\x78','\x60','\x70','\x6c','\x58','\x30','\x14','\x18','\x48','\x20','\x20','\x78','\x30','\x30','\xff','\xb0','\x50','\xff',
	'\xa0','\x50','\xa0','\x60','\x38','\xc0','\x78','\x40','\xff','\xc0','\x68','\xff','\xdc','\x70','\xb8','\x78','\x50','\x50','\x28','\x30',
	'\xa8','\x5c','\x40','\xd0','\x88','\x48','\xff','\xd4','\x60','\xff','\xd4','\x70','\xf0','\xb0','\x60','\xf8','\xb0','\x78','\xff','\xbc',
	'\x78','\xff','\xd8','\x88','\xff','\xc8','\x80','\x90','\x6c','\x58','\x98','\x70','\x70','\xff','\xf0','\xe8','\xff','\xff','\xe8','\xff',
	'\xfc','\xc8','\xff','\xfc','\xb8','\xff','\xff','\xc0','\xe8','\xd8','\xa8','\xd0','\xb4','\x90','\xe0','\xc4','\xa0','\xff','\xff','\xc8',
	'\xff','\xff','\xf0','\x30','\x1c','\x18','\x58','\x28','\x28','\x58','\x24','\x30','\xff','\x98','\x48','\xd8','\x78','\x40','\x18','\x08',
	'\x10','\x58','\x24','\x28','\x90','\x40','\x48','\xff','\xc8','\x68','\xff','\xd8','\x78','\x98','\x68','\x40','\x40','\x18','\x20','\x88',
	'\x40','\x48','\xff','\xc0','\x58','\xff','\xc4','\x68','\xc8','\x8c','\x50','\xa0','\x64','\x70','\xd8','\x84','\x88','\xf8','\xb4','\x88',
	'\xff','\xd4','\x88','\xff','\xdc','\x90','\xa0','\x70','\x58','\x48','\x1c','\x20','\xb0','\x68','\x68','\xe0','\x88','\x88','\xff','\xf0',
	'\xa8','\xff','\xf4','\xb8','\xb0','\x9c','\x78','\x20','\x00','\x00','\x48','\x10','\x18','\xb0','\x84','\x70','\xff','\xff','\xe8','\x60',
	'\x48','\x40','\x60','\x28','\x28','\x50','\x24','\x28','\xe0','\x6c','\x38','\xf0','\x84','\x38','\x40','\x1c','\x20','\x90','\x4c','\x48',
	'\x88','\x44','\x50','\xf8','\xb0','\x58','\xff','\xcc','\x70','\xf8','\xbc','\x68','\x68','\x34','\x38','\xff','\x94','\x98','\xff','\xb8',
	'\x68','\xff','\xc0','\x60','\xf8','\xb4','\x60','\x50','\x24','\x30','\xa8','\x60','\x58','\xb0','\x68','\x68','\xe8','\x9c','\x78','\xff',
	'\xd4','\x90','\xff','\xe4','\x98','\x68','\x48','\x38','\x58','\x1c','\x20','\x68','\x24','\x28','\xf8','\xd4','\x98','\xff','\xf4','\xb8',
	'\xf0','\xd8','\xa8','\x28','\x08','\x10','\x48','\x1c','\x20','\x68','\x38','\x30','\xff','\xff','\xe0','\x98','\x74','\x60','\x68','\x30',
	'\x30','\x50','\x24','\x28','\x30','\x18','\x20','\x38','\x18','\x20','\x58','\x24','\x30','\x88','\x48','\x38','\xd8','\x8c','\x40','\xff',
	'\xc4','\x68','\xff','\xcc','\x70','\xf8','\xb8','\x60','\xc0','\x80','\x80','\xff','\xac','\xa8','\xe0','\x90','\x50','\xff','\xc0','\x60',
	'\xff','\xc8','\x68','\x80','\x54','\x58','\xf0','\xa8','\xa0','\xd0','\x90','\x90','\xd0','\x90','\x88','\xff','\xd0','\x88','\xff','\xd8',
	'\x90','\xf8','\xc8','\x90','\x48','\x20','\x20','\x60','\x24','\x28','\xd0','\xa8','\x78','\xff','\xf4','\xb8','\xff','\xff','\xc0','\x38',
	'\x10','\x18','\x50','\x20','\x20','\x40','\x18','\x18','\x60','\x28','\x28','\x80','\x40','\x40','\x68','\x2c','\x28','\x50','\x28','\x28',
	'\x38','\x18','\x18','\x40','\x20','\x18','\xc0','\x50','\x38','\xff','\xa8','\x50','\xff','\xbc','\x60','\xff','\xc4','\x68','\xff','\xd0',
	'\x70','\xa8','\x5c','\x48','\xf8','\xcc','\xc8','\xe0','\x9c','\x98','\xb0','\x5c','\x38','\xff','\xc0','\x58','\xff','\xc4','\x60','\x88',
	'\x50','\x40','\xd0','\x80','\x80','\xc8','\x74','\x70','\x88','\x34','\x38','\xf0','\xa8','\x70','\xff','\xd0','\x90','\xff','\xe8','\xa0',
	'\x60','\x38','\x30','\x60','\x28','\x28','\xa8','\x78','\x58','\xff','\xf4','\xb0','\xff','\xff','\xc0','\x58','\x38','\x30','\x50','\x20',
	'\x28','\x48','\x20','\x20','\x68','\x30','\x30','\x78','\x38','\x38','\x68','\x30','\x30','\x58','\x2c','\x30','\x30','\x10','\x18','\xe0',
	'\x7c','\x30','\xff','\xa8','\x50','\xff','\xac','\x50','\xff','\xb8','\x58','\xd8','\x88','\x48','\x68','\x28','\x28','\x70','\x30','\x30',
	'\xe0','\x94','\x90','\xff','\xe8','\xe8','\xc0','\x5c','\x58','\xff','\xb8','\x50','\xff','\xc0','\x68','\xa0','\x6c','\x48','\xd0','\x94',
	'\x90','\xd8','\x98','\x90','\xd8','\x98','\x98','\xff','\xc0','\x90','\xff','\xcc','\x88','\xff','\xe0','\x98','\x70','\x4c','\x40','\x60',
	'\x28','\x28','\x98','\x5c','\x48','\xff','\xf8','\xb0','\xff','\xfc','\xb8','\x80','\x68','\x50','\x40','\x18','\x20','\x50','\x24','\x20',
	'\x70','\x34','\x30','\x80','\x3c','\x38','\x68','\x34','\x30','\x68','\x38','\x38','\x38','\x0c','\x18','\xff','\x98','\x48','\xff','\xa0',
	'\x50','\xf8','\x98','\x48','\x98','\x54','\x50','\x70','\x38','\x38','\x50','\x1c','\x20','\x40','\x14','\x18','\x68','\x2c','\x28','\xe8',
	'\xac','\xa8','\xff','\xf8','\xff','\xff','\xb8','\x50','\xff','\xb8','\x60','\xc0','\x7c','\x48','\x90','\x58','\x58','\xd0','\x7c','\x78',
	'\xe0','\x94','\x98','\xff','\xb4','\x88','\xff','\xcc','\x88','\xff','\xe0','\x98','\x78','\x48','\x40','\x88','\x40','\x40','\xc0','\x6c',
	'\x68','\xff','\xf4','\xb0','\xff','\xf4','\xb8','\xb0','\x94','\x70','\x30','\x10','\x10','\x60','\x2c','\x30','\x80','\x40','\x40','\x70',
	'\x38','\x38','\x58','\x2c','\x28','\x78','\x44','\x40','\x50','\x20','\x28','\xff','\x90','\x40','\xff','\xa0','\x48','\xa8','\x54','\x30',
	'\x70','\x3c','\x40','\xb8','\x60','\x60','\xc8','\x74','\x50','\xff','\xe8','\x78','\x38','\x14','\x10','\x70','\x2c','\x30','\xb8','\x7c',
	'\x80','\xff','\xb8','\x60','\xff','\xb8','\x60','\xf8','\xa0','\x58','\x80','\x50','\x58','\xc8','\x74','\x70','\x98','\x48','\x48','\xf0',
	'\xa0','\x70','\xff','\xc8','\x88','\xff','\xdc','\x90','\xa0','\x5c','\x50','\xe0','\x88','\x80','\xc0','\x68','\x70','\xff','\xdc','\x98',
	'\xff','\xf4','\xb0','\xe0','\xcc','\x98','\x38','\x0c','\x10','\x80','\x44','\x40','\x80','\x44','\x40','\x58','\x2c','\x28','\x40','\x1c',
	'\x18','\x60','\x2c','\x28','\x70','\x34','\x38','\xd8','\x70','\x30','\xff','\xa0','\x48','\xf0','\x84','\x40','\x20','\x00','\x10','\x50',
	'\x20','\x30','\xc0','\x74','\x58','\xff','\xd4','\x68','\x78','\x44','\x30','\x78','\x3c','\x40','\x50','\x20','\x28','\xb0','\x68','\x38',
	'\xff','\xb4','\x58','\xff','\xb4','\x60','\x50','\x28','\x30','\x90','\x54','\x58','\xd0','\x7c','\x60','\xff','\xc4','\x80','\xff','\xd0',
	'\x88','\xe8','\xa4','\x78','\xb0','\x60','\x60','\xa0','\x58','\x58','\x58','\x20','\x20','\xc0','\x98','\x70','\xff','\xec','\xb0','\xff',
	'\xf4','\xb0','\x28','\x00','\x00','\x60','\x2c','\x28','\x60','\x2c','\x28','\x48','\x20','\x20','\x38','\x18','\x18','\x40','\x1c','\x18',
	'\x60','\x28','\x28','\x78','\x38','\x38','\xd0','\x64','\x40','\xff','\xac','\x48','\xff','\xb0','\x50','\xe8','\x90','\x48','\xff','\xa8',
	'\x58','\xff','\xd0','\x68','\xe0','\x9c','\x70','\xff','\xcc','\xc8','\xff','\xa0','\x68','\xff','\xa4','\x48','\xff','\xb4','\x50','\xff',
	'\xb4','\x58','\xff','\xa4','\x60','\xff','\xb4','\x70','\xff','\xc0','\x78','\xff','\xb4','\x70','\xc8','\x80','\x60','\x88','\x40','\x40',
	'\x70','\x34','\x30','\x68','\x2c','\x28','\xd0','\x9c','\x78','\xff','\xec','\xa8','\xff','\xff','\xb8','\xff','\xff','\xc0','\xff','\xf8',
	'\xb8','\x78','\x58','\x48','\x40','\x1c','\x18','\x48','\x20','\x20','\x40','\x1c','\x18','\x30','\x14','\x18','\x38','\x18','\x18','\x50',
	'\x24','\x28','\x70','\x3c','\x40','\x98','\x50','\x48','\xc0','\x70','\x50','\xa0','\x60','\x40','\x80','\x48','\x30','\x48','\x1c','\x20',
	'\x48','\x1c','\x20','\x70','\x38','\x38','\xa8','\x5c','\x50','\xc8','\x7c','\x70','\xe0','\x88','\x80','\xe0','\x80','\x78','\xd8','\x7c',
	'\x78','\xc0','\x6c','\x68','\xb0','\x5c','\x58','\x98','\x54','\x50','\x98','\x4c','\x50','\x98','\x4c','\x50','\x90','\x50','\x48','\x90',
	'\x4c','\x48','\x98','\x50','\x48','\x90','\x48','\x40','\x78','\x3c','\x38','\x60','\x24','\x28','\x58','\x24','\x28','\x48','\x20','\x20',
	'\x50','\x24','\x20','\x58','\x28','\x28','\x60','\x2c','\x28','\x58','\x28','\x28','\x40','\x1c','\x20','\x38','\x18','\x18','\x40','\x18',
	'\x18','\x50','\x28','\x28','\x80','\x4c','\x48','\xb0','\x5c','\x58','\xc0','\x78','\x78','\xa8','\x60','\x60','\x88','\x4c','\x48','\x68',
	'\x38','\x30','\x58','\x28','\x28','\x50','\x28','\x28','\x58','\x28','\x28','\x60','\x2c','\x28','\x68','\x2c','\x30','\x70','\x34','\x30',
	'\x78','\x3c','\x38','\x78','\x3c','\x38','\x88','\x40','\x38','\x88','\x40','\x40','\x88','\x44','\x40','\x80','\x44','\x40','\x70','\x38',
	'\x30','\x58','\x28','\x28','\x50','\x20','\x20','\x50','\x20','\x20','\x58','\x28','\x28','\x60','\x2c','\x28','\x68','\x2c','\x28','\x58',
	'\x28','\x28','\x48','\x24','\x20','\x68','\x30','\x30','\x70','\x34','\x30','\x60','\x30','\x30','\x48','\x24','\x20','\x38','\x1c','\x18',
	'\x38','\x1c','\x18','\x48','\x20','\x20','\x60','\x30','\x30','\x90','\x50','\x48','\xc0','\x6c','\x68','\xd8','\x78','\x70','\xe0','\x78',
	'\x70','\xd8','\x7c','\x70','\xc8','\x70','\x68','\xb8','\x6c','\x68','\xa8','\x60','\x58','\xa0','\x54','\x50','\x98','\x50','\x48','\x90',
	'\x4c','\x48','\x88','\x44','\x40','\x78','\x3c','\x38','\x68','\x30','\x30','\x60','\x30','\x30','\x60','\x30','\x30','\x68','\x34','\x30',
	'\x70','\x34','\x30','\x70','\x38','\x38','\x68','\x38','\x38','\x60','\x2c','\x30','\x50','\x24','\x28','\x48','\x20','\x20','\x38','\x18',
	'\x18','\x38','\x18','\x18','\x50','\x24','\x28','\x68','\x38','\x38','\x80','\x40','\x40','\x78','\x3c','\x38','\x68','\x34','\x38','\x50',
	'\x28','\x28','\x48','\x20','\x20','\x40','\x1c','\x20','\x40','\x1c','\x18','\x50','\x20','\x20','\x60','\x2c','\x28','\x70','\x34','\x38',
	'\x80','\x40','\x40','\x88','\x44','\x40','\x88','\x48','\x40','\x88','\x48','\x40','\x80','\x44','\x40','\x78','\x40','\x38','\x78','\x40',
	'\x38','\x78','\x3c','\x38','\x78','\x3c','\x38','\x78','\x3c','\x38','\x78','\x3c','\x38','\x70','\x38','\x38','\x68','\x34','\x30','\x58',
	'\x2c','\x28','\x50','\x24','\x20','\x40','\x20','\x20','\x40','\x1c','\x18','\x48','\x20','\x20','\x40','\x1c','\x20','\x38','\x18','\x18',
	'\x38','\x14','\x18','\x38','\x18','\x18','\x48','\x20','\x20','\x60','\x2c','\x30','\x78','\x40','\x40','\x88','\x48','\x48','\x90','\x48',
	'\x48','\x88','\x44','\x48','\x78','\x3c','\x40','\x70','\x38','\x30','\x60','\x30','\x30','\x58','\x2c','\x30','\x58','\x2c','\x28','\x60',
	'\x2c','\x28','\x60','\x2c','\x28','\x60','\x30','\x28','\x68','\x34','\x30','\x68','\x34','\x30','\x70','\x34','\x30','\x68','\x34','\x30',
	'\x68','\x34','\x30','\x68','\x30','\x30','\x58','\x2c','\x28','\x50','\x24','\x28','\x50','\x20','\x20','\x48','\x20','\x20','\x50','\x24',
	'\x20','\x50','\x24','\x20','\x58','\x28','\x28','\x58','\x24','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40',
	'\x20','\x20','\x40','\x1c','\x20','\x50','\x24','\x28','\x50','\x24','\x28','\x58','\x24','\x28','\x58','\x28','\x28','\x60','\x2c','\x30',
	'\x70','\x34','\x38','\x88','\x40','\x40','\x88','\x40','\x40','\x88','\x3c','\x40','\x80','\x3c','\x40','\x78','\x38','\x38','\x78','\x38',
	'\x38','\x78','\x38','\x40','\x78','\x38','\x40','\x68','\x30','\x30','\x60','\x2c','\x30','\x50','\x24','\x28','\x40','\x20','\x20','\x38',
	'\x1c','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20',
	'\x40','\x1c','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20',
	'\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x38','\x1c','\x20','\x40','\x20','\x20','\x50',
	'\x24','\x28','\x50','\x24','\x28','\x50','\x28','\x28','\x60','\x2c','\x30','\x68','\x34','\x30','\x70','\x34','\x38','\x78','\x38','\x38',
	'\x78','\x38','\x40','\x80','\x3c','\x40','\x80','\x3c','\x40','\x80','\x38','\x40','\x70','\x34','\x38','\x58','\x28','\x28','\x48','\x20',
	'\x20','\x48','\x20','\x20','\x40','\x20','\x20','\x48','\x20','\x20','\x48','\x20','\x20','\x48','\x24','\x28','\x50','\x24','\x28','\x48',
	'\x24','\x28','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x48','\x20','\x20','\x50','\x24','\x28',
	'\x48','\x20','\x28','\x40','\x20','\x20','\x40','\x1c','\x20','\x50','\x24','\x28','\x60','\x2c','\x30','\x58','\x28','\x28','\x58','\x28',
	'\x28','\x50','\x28','\x28','\x38','\x18','\x18','\x38','\x18','\x18','\x38','\x1c','\x20','\x40','\x1c','\x20','\x50','\x24','\x28','\x58',
	'\x28','\x28','\x58','\x28','\x28','\x50','\x28','\x28','\x60','\x2c','\x30','\x68','\x30','\x30','\x70','\x30','\x38','\x70','\x34','\x38',
	'\x70','\x34','\x38','\x70','\x34','\x38','\x60','\x30','\x30','\x60','\x2c','\x30','\x58','\x28','\x28','\x48','\x24','\x28','\x40','\x20',
	'\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x50','\x24','\x28','\x58','\x28','\x28','\x58',
	'\x28','\x28','\x60','\x2c','\x30','\x70','\x34','\x38','\x78','\x38','\x38','\x80','\x3c','\x40','\x88','\x40','\x40','\x90','\x40','\x48',
	'\x88','\x40','\x40','\x78','\x38','\x38','\x78','\x38','\x38','\x68','\x30','\x30','\x50','\x24','\x28','\x48','\x20','\x20','\x48','\x20',
	'\x20','\x48','\x20','\x20','\x48','\x24','\x28','\x48','\x20','\x28','\x48','\x20','\x20','\x48','\x20','\x20','\x48','\x20','\x20','\x48',
	'\x20','\x20','\x40','\x20','\x20','\x58','\x28','\x28','\x58','\x28','\x28','\x58','\x28','\x28','\x40','\x20','\x20','\x40','\x20','\x20',
	'\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x40','\x1c',
	'\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x40','\x1c','\x20','\x48','\x24','\x28','\x58','\x2c','\x28','\x70','\x34','\x38','\x80',
	'\x38','\x40','\x88','\x40','\x40','\x80','\x3c','\x40','\x78','\x38','\x38','\x78','\x38','\x38','\x70','\x34','\x38','\x58','\x28','\x28',
	'\x50','\x24','\x28','\x48','\x24','\x28','\x48','\x24','\x28','\x48','\x20','\x20','\x48','\x20','\x20','\x40','\x20','\x20','\x40','\x20',
	'\x20','\x48','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40',
	'\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20',
	'\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x48','\x20',
	'\x20','\x48','\x20','\x20','\x50','\x24','\x28','\x58','\x28','\x28','\x60','\x2c','\x30','\x60','\x2c','\x30','\x68','\x30','\x30','\x60',
	'\x2c','\x30','\x50','\x24','\x28','\x48','\x20','\x20','\x48','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20','\x40','\x20','\x20',
	'\x40','\x20','\x20','\x40','\x20','\x20',
};

        bool Window::iconify(void)
        {
            return ( SDL_WM_IconifyWindow() != 0 );
        }

        //needs to be redone
        bool Window::toggleFullScreen(void)
        {
            //This only works for X11
#if defined ( __MINGW32__) || defined ( __WIN32__) || defined( WIN32 ) ||  defined( _WINDOWS ) //check for WIN32
            //workaround for win32 ??
#ifdef DEBUG
            Log << nl << "Ignoring ToggleFullScreen() on Windows platform..." << std::endl;
#endif
            //return setFullscreen(true);
            //looks like it doesnt work...
            return false;
#else
#ifdef DEBUG

            Log << nl << "Calling SDL_WM_ToggleFullScreen(" << _screen->_surf << ")" << std::endl;
#endif

            return ( SDL_WM_ToggleFullScreen(_screen->_surf) != 0 ) ;
#endif

        }

        void Window::grabInput()
        {
            SDL_WM_GrabInput( SDL_GRAB_ON );
        }

        void Window::releaseInput()
        {
            SDL_WM_GrabInput( SDL_GRAB_OFF );
        }

        bool Window::isInputGrabbed()
        {
            return SDL_WM_GrabInput( SDL_GRAB_QUERY ) == SDL_GRAB_ON;
        }




        void Window::setCaption(std::string title, std::string icon)
        {
            _title=title;
            _icon=icon;
            SDL_WM_SetCaption(_title.c_str(), _icon.c_str());
            //seticon needed or ?
        }

        bool Window::setIcon(std::string iconfilename)
        {
            bool res=false;
            SDL_Surface * icon;
            ///TODO : This should use an RGB Surface to avoid code duplication
            if (iconfilename != "" ) icon=SDL_LoadBMP(iconfilename.c_str());
            else icon = SDL_LoadBMP(DEFAULT_WINDOW_ICON); // todo : use embedded resource...
            if ( icon != NULL )
            {
                _icon=iconfilename;
                SDL_WM_SetIcon( icon , NULL);
                res = true;
            }
            else
            {
                Log << nl << "Unable to load the icon " << iconfilename << " : " << GetError() << std::endl;
            }
            return res;
        }

        //old version
        void Window::getCaption(std::string & title, std::string & icon)
        {
            char * t="";
            char * i="" ;
            SDL_WM_GetCaption(&t,&i);
            title=std::string(t);
            icon=std::string(i);
        }

        std::string Window::getTitle()
        {
            char * t = "" ;
            SDL_WM_GetCaption(&t,NULL);
            return std::string(t);

        }
        std::string Window::getIconName()
        {
            char * i  = "";
            SDL_WM_GetCaption(NULL,&i);
            return std::string(i);
        }

        bool Window::setResizable(bool val)
        {
            bool res = true;
            if (_screen == NULL )
                VideoSurface::setResizable(val);
            else if (_screen->isResizableset() !=val ) //if called inside mainLoop while screen is active
            {
                if (! resetDisplay(_screen->getWidth(),_screen->getHeight()))
                    res=false;
            }
            return res;
        }

        bool Window::setFullscreen(bool val)
        {
#ifdef DEBUG
            Log << nl << "Window::setFullscreen(" << val << ") called" << std::endl;
#endif

            bool res = true;
            if (_screen == NULL )
                VideoSurface::setFullscreen(val);
            else
            {
#ifdef DEBUG
                Log << nl << _screen->isFullScreenset() << " != " << val << std::endl;
#endif

                if (_screen->isFullScreenset() != val ) //if called inside mainLoop while screen is active
                {
                    if (! resetDisplay(_screen->getWidth(),_screen->getHeight()))
                        res=false;
                }
            }
            return res;
        }

        bool Window::setNoFrame(bool val)
        {
            bool res = true;
            if (_screen == NULL )
                VideoSurface::setNoFrame(val);
            else if (_screen->isNoFrameset() !=val )  //if called inside mainLoop while screen is active
            {
                if (! resetDisplay(_screen->getWidth(),_screen->getHeight()))
                    res=false;
            }
            return res;
        }
#ifdef HAVE_OPENGL
        bool Window::setOpenGL(bool val)
        {
            bool res = true;
            if (_screen == NULL )
                VideoSurface::setOpenGL(val);
            else if ( _screen->isOpenGLset() !=val ) //if called inside mainLoop while screen is active
            {
                VideoSurface::setOpenGL(val);
                if (! resetDisplay(_screen->getWidth(),_screen->getHeight()))
                    res=false;
            }
            return res;
        }
#endif


        Window::Window(std::string title,std::string icon)
                : _title(title), _icon(icon),_background(Color(0,0,0)),_engine(NULL)
#ifdef HAVE_OPENGL
                ,_glengine(NULL)
#endif
        {
#ifdef DEBUG
            Log << nl << "Window::Window(" << title << ", " << icon << ") called ..." ;
#endif

            try
            {
                _eventmanager = new EventManager();
                _videoinfo = new VideoInfo();
#ifdef HAVE_OPENGL

                _userglengine=false;
                _glmanager = new GLManager();

#endif

                _userengine=false;

            }
            catch (std::exception &e)
            {
                Log << nl << e.what() << std::endl;
            }
            _screen=NULL;
            //setting the static videoInfo to be used by all surfaces...

            BaseSurface::_vinfo = _videoinfo;

            setIcon(_icon);
            setTitle(_title);

#ifdef DEBUG

            Log << nl << "Window::Window(" << title << ", " << icon << ") done @ "<< this ;
#endif

        }

        Window::~Window()
        {
#ifdef DEBUG
            Log << nl << "Window::~Window() called ..." << std::endl;
#endif
#ifdef HAVE_OPENGL

            if (!_userglengine)
                delete _glengine, _glengine = NULL;
            delete _glmanager, _glmanager = NULL;
#endif

            if (!_userengine)
                delete _engine, _engine = NULL;
            delete _videoinfo, _videoinfo = NULL;
            BaseSurface::_vinfo = NULL;
#ifdef DEBUG

            Log << nl << "Window::~Window() done." << std::endl;
#endif

        }

            //BGColor works only on 2DWindow
            void Window::setBGColor(const Color & color)
            {
                _background = color;
                if (_screen != NULL)
                    _screen->setBGColor(_background);
            }

        void Window::setEngine (Engine *engine)
        {
#ifdef DEBUG
            Log << nl << "Window::setEngine(" << engine << ") called ...";
#endif
            assert(engine);
            _userengine=true;
            _engine=engine;
            if (_screen != NULL)
            {
                _screen->setEngine(_engine);
                _engine->_screen=_screen;
            }

#ifdef DEBUG
            Log << nl << "Window::setEngine(" << engine << ") done.";

#endif

        }

#ifdef HAVE_OPENGL
        void Window::setGLEngine (Engine* glengine)
        {
#ifdef DEBUG
            Log << nl << "Window::setGLEngine(" << glengine << ") called ...";
#endif
            assert(glengine);
			_userglengine=true;
            _glengine=glengine;
            if (_screen != NULL&&_screen->isOpenGLset())
                {
                    _screen->setEngine(_glengine);
                    _glengine->_screen=_screen;
                }
#ifdef DEBUG
            Log << nl << "Window::setGLEngine(" << glengine << ") done.";
#endif

        }
#endif




        VideoSurface* Window::resetDisplay( int width, int height)
        {
#ifdef DEBUG
            Log << nl << "Window::reset(" << width << "," << height << ") called ..." << std::endl;
#endif

            bool res = false;
            int _bpp=VideoSurface::getSuggestedBPP(width, height);
            //but beware about bpp == 0...
            if (_bpp == 0 )
            {//0 as return code mean the current format is not supported
                Log << nl << "The requested video mode is not supported under any bit depth. Display reset cancelled !";
            }
            else
            {
                Log << nl << "SDL will use " << width << "x" << height << "@" <<_bpp;
                //create a new screen
                try
                {
                    //REMINDER : SDL_SetVideoMode, takes care of freeing the old surfaces (according to the doc)
#ifdef HAVE_OPENGL
                    //if opengl support compiled and opengl enable on screen then initialise it
                    if ( (SDL_OPENGL & VideoSurface::_defaultflags) !=0 )
                    {
                        _screen = new GLSurface(width, height, _bpp,_glmanager);
                        if ( _screen!=NULL && _glengine != NULL)
                        {
                            res =_screen->setEngine(_glengine);
                            _glengine->_screen=_screen;
                        }
                    }
                    else
                    {
#endif

                        _screen = new VideoSurface(width, height, _bpp);
                        if ( _screen!=NULL && _engine != NULL)
                        {
                                                     res =_screen->setEngine(_engine);
                                                     _engine->_screen=_screen;
                        }
#ifdef HAVE_OPENGL

                    }
#endif

                    if (_screen != NULL)
                    {
                        _screen->setBGColor(_background);
                        res=true;
                    }
                }
                catch(std::exception & e)
                {
                    Log << e.what();
                }
            }
#ifdef DEBUG
            Log << nl << "Window::reset(" << width << "," << height << ") done." << std::endl;
#endif

            //return res;
			return _screen;

        }

        VideoSurface* Window::resizeDisplay (int width, int height) const
        {

#ifdef DEBUG
            Log << nl << "Window::resize() called ...";
            assert (_screen);
#endif

            bool res = false;
            if (_screen != NULL )
            {
                _screen->resize(width,height);
            }

#ifdef DEBUG
            Log << nl << "Window::resize() done.";
#endif

            //return res;
			return _screen;
        }

        bool Window::mainLoop()
        {
            bool res = false;
#ifdef DEBUG

            assert(_eventmanager);
#endif

            if (_eventmanager != NULL)
            {

#ifdef DEBUG
                assert (_screen);
#endif

                if (_screen !=NULL)
                {
                    while (!(_eventmanager->quitRequested()))
                    {
                        _eventmanager->handleAll();

                        _screen->update();
                    }
                    delete _screen; // to delete the wrapper class (not the actual video surface in memory...)
                    _screen = NULL;
                    res = true;
                }
                else
                {
                    Log << nl << "ERROR : DisplaySurface @ " << _screen << " can't be used !" << std::endl;
                    Log  << nl <<" Ignoring mainLoop call." << std::endl;
                }
                //Loop finished, the EventManager should be reinitialized
                delete _eventmanager;
                _eventmanager = new EventManager();
            }
            else
            {
                Log << nl << "ERROR : EventManager @ " << _eventmanager;
            }
            if (!res)
            {
                Log  << nl << "An error occured when trying to launch the main loop, make sure you have initialized everything." << std::endl;
                Log  << nl <<" Ignoring mainLoop call." << std::endl;
            }
            return res;

        }
    }
}
