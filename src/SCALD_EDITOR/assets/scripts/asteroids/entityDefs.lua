AsteroidDefs =
{
	asteroid_big = 
	{
		group = "asteroids",
		components =
		{
			transform = {
				position = { x = -100, y = -100 },
				scale = { x = 1, y = 1},
				rotation = 0
			},
			sprite = {
				asset_name = "ast_1",
				width = 120,
				height = 97,
				start_x = 0,
				start_y = 0,
				layer = 2
			}
		}
	},
	asteroid_small = 
	{
		group = "asteroids",
		components =
		{
			transform = {
				position = { x = -100, y = -100 },
				scale = { x = 1, y = 1},
				rotation = 0
			},
			sprite = {
				asset_name = "ast_2",
				width = 43,
				height = 43,
				start_x = 0,
				start_y = 0,
				layer = 2
			}
		}
	}
}

ShipDefs =
{
	blue_ship = 
	{
		group = "ship",
		components =
		{
			transform = {
				position = { x = 320, y = 240 },
				scale = { x = 1, y = 1},
				rotation = 0
			},
			sprite = {
				asset_name = "ship",
				width = 104,
				height = 83,
				start_x = 0,
				start_y = 0,
				layer = 2
			}
		}
	}
}