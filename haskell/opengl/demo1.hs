import Graphics.Rendering.OpenGL
import Graphics.UI.GLUT
import Graphics.UI.GLUT.Fonts
import Data.IORef

data State = State { pos    :: Position
                   , buttons:: (Maybe MouseButton)
                   } deriving (Show)

myPoints :: GLfloat -> [(GLfloat, GLfloat, GLfloat)]
myPoints foo = do
    map (\k -> let r = k  in (400 + r * sin(foo + 2 * pi * k / 23), 200 + r * cos(foo + 2 * pi * k / 23), 0.0)) [1 .. 100]

makeVertexes2d = mapM_ (\ (x, y) -> vertex $ Vertex3 x y (0::GLfloat))

sparse :: [(GLfloat, GLfloat)] -> [(GLfloat, GLfloat)]
sparse arr =
    let d (x1, y1) (x2, y2) = sqrt((x1 - x2) ^ 2 + (y1 - y2) ^ 2) in
    foldl (\acc x -> case acc of 
                         [] -> [x]
                         a  -> if d x (last a) > 50
                                  then a ++ [x] 
                                  else a
          )  [] arr
          
main = do 
  (progname, _) <- getArgsAndInitialize
  createWindow "Hello World"
  matrixMode  $= Projection
  windowSize  $= Size 800 500  
  polygonMode $= (Line, Line)
  reshapeCallback $= Just reshape
  path <- newIORef ([[]] :: [[(GLfloat, GLfloat)]])
  foo <- newIORef 0.0
  state <- newIORef (State (Position 0 0) Nothing)
  mode <- newIORef (0::Int)
  displayCallback $= display state foo path mode
  motionCallback $= Just (mouse state path)
  passiveMotionCallback  $= Just (mouse state path)
  keyboardMouseCallback $= Just (keyboardMouse (state, path, mode))
  idleCallback $= Just (idle foo)  
  mainLoop
 
motion path pos@(Position x y) = do
    p <- get path
    path $= init p ++ [last p ++ [(fromIntegral x, fromIntegral y)]]
    
mouse state path pos@(Position x y) = do
    s@(State _ buttons) <- get state
    p <- get path
    state $= State pos buttons
    if buttons == Just LeftButton 
        then path $= init p ++ [last p ++ [(fromIntegral x, fromIntegral y)]]         
        else return ()
    
keyboardMouse (state, path, mode) (MouseButton LeftButton) Up _ pos@(Position x y) = do    
    state $= State pos Nothing
    p <- get path
    path $= p ++ [[]]

keyboardMouse (state, path, mode) (MouseButton LeftButton) Down _ pos@(Position x y) = do    
    state $= State pos (Just LeftButton)    
    mapM_ (checkMouseButton mode pos) [0..4]

keyboardMouse (state, path, mode) (MouseButton RightButton) Down _ pos@(Position x y) = do    
    path $= [[]]    
    
keyboardMouse (state, path, mode) key dest _ pos = do
    print $ "unknown key " ++ (show key)
    
idle foo = do 
  f <- get foo
  foo $= f + 0.01
  postRedisplay Nothing
  
selectPrim mode = 
	let mt = [(0, TriangleStrip), (1, Points)]
	in head [snd a | a <- mt, fst a == mode]
    
foo x1 y1 = 
    let b = x1 ^ 2 + y1 ^ 2
        c = (x1 * y1) ^ 2 in 
        (b + sqrt (b^2 - 4 * c)) / 2
 
normA (x1, y1) (x2, y2) = (x1 - y2 + y1, y1 + x2 - x1) 
normB (x1, y1) (x2, y2) = (x1 + y2 - y1, y1 - x2 + x1)
 
squareStripTransform :: [(GLfloat, GLfloat)] -> [(GLfloat, GLfloat)]
squareStripTransform [] = []
squareStripTransform (_:[]) = []
squareStripTransform a = 
    concat [
        let p1 = a !! i
            p2 = a !! (i + 1) in        
            [normA p1 p2, normB p1 p2] | i <- [0 .. length a - 2]
    ]
    
squareTransform :: [(GLfloat, GLfloat)] -> [(GLfloat, GLfloat)]
squareTransform [] = []
squareTransform (_:[]) = []
squareTransform a = 
    concat [ let p1 = a !! i
                 p2 = a !! (i + 1) 
                 n1 = normA p1 p2
                 n2 = normB p1 p2 in       
                 if mod (i + 1) 2 /= 0 then [n1, n2] else [n2, n1] | i <- [0 .. length a - 2] ]
 
    
triangleTransform :: [(GLfloat, GLfloat)] -> [(GLfloat, GLfloat)]
triangleTransform [] = []
triangleTransform a = 
    [let (x1, y1) = a !! i
         (x2, y2) = a !! (i + 1) 
         v1 = (x1 - y2 + y1, y1 + x2 - x1) 
         v2 = (x1 + y2 - y1, y1 - x2 + x1) in 
         if (mod i 2 == 0) then v1 else v2 | i <- [0 .. length a - 2]]
         
display state foo path mode = do 
  clear [ColorBuffer]
  f <- get foo
  p <- get path
  m <- get mode
  State pos _ <- get state
  case m of 
    0 -> mapM_ ((renderPrimitive TriangleStrip) . makeVertexes2d . triangleTransform ) p
    1 -> mapM_ ((renderPrimitive Triangles) . makeVertexes2d . triangleTransform) p
    2 -> mapM_ ((renderPrimitive QuadStrip) . makeVertexes2d . squareStripTransform) p
    3 -> mapM_ ((renderPrimitive Quads) . makeVertexes2d . squareTransform) p
    4 -> mapM_ ((renderPrimitive TriangleFan) . makeVertexes2d) p
  renderMenu pos mode
  flush
                                                                          
checkMouseButton mode (Position x y) i = do
    (Size w h) <- get windowSize
    let width = 15::GLfloat
        ofsx  = fromIntegral w - 160 + (2 * width) * fromIntegral i
        ofsy  = 20
        fx = fromIntegral x
        fy = fromIntegral y 
        in if fx > ofsx && fx < ofsx + width &&
              fy > ofsy && fy < ofsy + width
              then mode $= i
              else return ()

drawButton :: Position -> IORef Int -> Int -> IO ()
drawButton (Position x y) mode i = do
    (Size w h) <- get windowSize
    m <- get mode
    let width = 15::GLfloat
        ofsx  = fromIntegral w - 160 + (2 * width) * fromIntegral i
        ofsy  = 20
        fx = fromIntegral x
        fy = fromIntegral y 
        lw    = if m == i || 
                   fx > ofsx && fx < ofsx + width &&
                   fy > ofsy && fy < ofsy + width then 3 else 1
        in do lineWidth $= lw
              if m == i then polygonMode $= (Fill, Fill) else return ()
              renderPrimitive Polygon $ makeVertexes2d 
                [(ofsx, ofsy), (ofsx + width, ofsy), (ofsx + width, ofsy + width), (ofsx, ofsy + width)]
              polygonMode $= (Line, Line)
              lineWidth $= 1        
    
renderMenu pos mode = do
    (Size w h) <- get windowSize
    mapM_ (drawButton pos mode) [0..4]
    flush
  
projection xl xu yl yu = do 
  matrixMode $= Projection
  loadIdentity
  ortho xl xu yl yu (-1) 1
  matrixMode $= Modelview 0
  
reshape s@(Size w h) = do
  viewport $= (Position 0 0, s)
  let wd = (fromIntegral w)::GLdouble 
      hd = (fromIntegral h)::GLdouble 
      in do projection (0) wd (hd) 0
  postRedisplay Nothing