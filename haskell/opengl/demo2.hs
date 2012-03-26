import Graphics.Rendering.OpenGL
import Graphics.UI.GLUT
import Control.Concurrent
import Data.IORef
import System.Random

data State = State { pos    :: Position
                   , buttons:: (Maybe MouseButton)
                   } deriving (Show)

refString = [[1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1]
            ,[1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0]
            ,[1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0]
            ,[1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0]
            ,[1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0]]
            
makeVertexes2d = mapM_ (\ (x, y) -> vertex $ Vertex3 x y (0::GLfloat))
         
main = do 
  (progname, _) <- getArgsAndInitialize
  createWindow "Hello World"
  initialDisplayMode $= [DoubleBuffered, WithAlphaComponent]
  --initialDisplayCapabilities $= [With DisplayRGBA, Where DisplayAlpha IsNotLessThan 8]
  --alphaFunc $=  Just (Always, 1.0)
  blend $= Enabled
  blendEquation $= FuncAdd
  blendFunc $= (SrcAlpha, OneMinusSrcAlpha)
  matrixMode  $= Projection
  windowSize  $= Size 800 500  
  polygonMode $= (Line, Line)
  reshapeCallback $= Just reshape
  state <- newIORef (State (Position 0 0) Nothing)
  mode <- newIORef (0::Int)
  ref <- newIORef (0.0::GLfloat)
  stars <- newIORef ([]::[(GLfloat, GLfloat, GLfloat, GLfloat)])
  -- stars $= [(100, 100, 80, 0.3)]
  displayCallback $= display state stars mode ref
  motionCallback $= Just (mouse ref state)
  passiveMotionCallback  $= Just (mouse ref state)
  keyboardMouseCallback $= Just (keyboardMouse (state, mode, ref))
  idleCallback $= Just (idle stars) 
  mainLoop
    
mouse ref state pos@(Position x y) = do
    s@(State _ buttons) <- get state
    state $= State pos buttons
    if buttons == Just LeftButton
        then checkRef pos ref
        else return ()

keyboardMouse (state, mode, ref) (MouseButton LeftButton) Up _ pos@(Position x y) = do    
    state $= State pos Nothing

keyboardMouse (state, mode, ref) (MouseButton LeftButton) Down _ pos@(Position x y) = do    
    state $= State pos (Just LeftButton)    
    mapM_ (checkMouseButton mode pos) [0..4]    
    
keyboardMouse (state, mode, ref) key dest _ pos = do
    print $ "unknown key " ++ (show key)
    
idle stars = do 
  s <- get stars
  --stars $= filter (\(_, y, _, _) -> y < 200)
  let n = 5
      diff = n - length s
  if diff > 0
    then do x <- randomRIO (0.0, 1.0)
            r <- randomRIO (20.0, 100.0)
            a <- randomRIO (0, pi)
            stars $= s ++ [(x * 800, -r, r, a)]
    else stars $= map (\(x, y, r, rot) -> (x, y + 20/r, r, rot)) (filter (\(_, y, _, _) -> y < 600) s)
  postRedisplay Nothing
  threadDelay (10^4)
 
drawRefPart (Size width _) (i, j) = do
    let w = 3
        x = fromIntegral width - 70 + fromIntegral i * w
        y = 80 + fromIntegral j * w
        sq = [(x, y), (x + w, y), (x + w, y + w), (x, y + w)] 
    renderPrimitive Polygon $ makeVertexes2d sq    
 
drawRef = do
    polygonMode $= (Fill, Fill)
    size <- get windowSize
    mapM (drawRefPart size) [(i, j) | i <- [0..10], j <-[0..4], (refString !! j) !! i == 1]
         
drawPatchPart ix iy = do
    let nk = 5
        w = 20
        a = 3
        f = 0.05
        it = [0 .. nk-1]
        vs = [(-a + w * i + w * nk * ix, -a + w * nk * iy + w * j) | i <- it, j <- it]
        vst = concat $ map (\(x, y) -> [(x, y), (x + w, y), (x + w, y + w), (x, y + w)]) vs
        vstt = map (\(x, y) -> (x + a * sin(f * y), y + a * cos(f * x))) vst
    renderPrimitive Quads $ makeVertexes2d vstt

drawPatch = do
    polygonMode $= (Fill, Fill)
    mapM (\(i, j) -> do currentColor $= if mod (i + j) 2 == 0 then Color4 1 1 1 1 else Color4 0.3 0.47 0.26 1
                        drawPatchPart (fromIntegral i) (fromIntegral j)                      
          ) [(i, j) | i <- [0..6], j <- [0..5]]
          
checkRef (Position x y) ref = do
    (Size w _) <- get windowSize    
    let xoffs = fromIntegral w - 50
        yoffs = 120
        h = 300        
        v = (fromIntegral y - yoffs) / h
    if abs (x - xoffs) < 20 && v >= 0 && v <= 1
       then ref $= v
       else return ()
    
drawRefControl refVal = do
    (Size w _) <- get windowSize
    currentColor $= Color4 1 1 1 1
    let xoffs = fromIntegral w - 50
        yoffs = 120
        h = 300        
        
    renderPrimitive Lines $ makeVertexes2d [(xoffs, yoffs), (xoffs, yoffs + h)]
    polygonMode $= (Fill, Fill)
    renderPrimitive Triangles $ makeVertexes2d [(xoffs - 10, yoffs + h * refVal)
                                               ,(xoffs +  7, yoffs + h * refVal - 10)
                                               ,(xoffs +  7, yoffs + h * refVal + 10)]    

drawStar (x, y, r, rot) = do
    let a = [rot + i/5.0 * 2.0 * pi | i <- [0..4]]
        rm = r * 0.3819660112501051
        dots = map (\alpha -> (x + rm * sin alpha, y + rm * cos alpha)) a
        rad36 = pi * 36 / 180
        triangles = concat $ 
            map (\alpha -> [(x + rm * sin alpha, y + rm * cos alpha)
                           ,(x + r* sin (alpha + rad36), y + r * cos (alpha + rad36))
                           ,(x + rm* sin (alpha + 2*rad36), y + rm * cos (alpha + 2*rad36))]) a
    
    currentColor $= Color4 1 0.8431 0 0.3
    renderPrimitive Polygon $ makeVertexes2d dots
    renderPrimitive Triangles $ makeVertexes2d triangles
  
display state stars mode ref = do 
  clear [ColorBuffer]
  m <- get mode
  State pos _ <- get state 
  r <- get ref  
  s <- get stars
  drawPatch
  drawRefControl r
  drawRef  
  currentColor $= Color4 0 0 0 1
  polygonMode $= (Fill, Fill)
  mapM drawStar s
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
              if m == i then polygonMode $= (Fill, Fill) else polygonMode $= (Line, Line)
              renderPrimitive Polygon $ makeVertexes2d 
                [(ofsx, ofsy), (ofsx + width, ofsy), (ofsx + width, ofsy + width), (ofsx, ofsy + width)]
              lineWidth $= 1        
    
renderMenu pos mode = do
    (Size w h) <- get windowSize
    currentColor $= Color4 1 1 1 1
    mapM_ (drawButton pos mode) [0..4]    
  
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