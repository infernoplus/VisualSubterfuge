shader : {
  name : 'basic shader',
  glsl : '/home/inferno/dev/VisualSubterfuge/data/basic',

  textures : ['/home/inferno/dev/VisualSubterfuge/data/tex2.png','/home/inferno/dev/VisualSubterfuge/data/tex1.png'],

  uniforms : {
    color : [1.0f,0.1f,0.4f,1.0f],
    scale : 1.1f
  }
}

//strict typing
// if value == true or false then type = boolean
// if value is surrounded by single quotes then type = string (ex: 'hello' or 'this is a string')
// if value is a number postfixed by f then type = float (ex: 1.0f or 123f or -0.21312f)
// if value is a number then type = int (ex: 1 or 123414 or -123)

//support
// arrays only support prim types, no objects or arrays!
