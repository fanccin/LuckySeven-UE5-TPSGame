# LuckySeven-UE5-TPSGame
## Stage1 Character Readme by 이인구

### 조작관련
* 이동: WASD | (기본이 뛰는 것)
* 걷기: SHIFT
* LOOK: Mouse
* 점프: Space

### 기본 로직
* 캐릭터의 Stats (이동 점프 방향 공중제어 걷기 공격 데미지) 등은 DataTable 생성해서 거기에서 관리 
* NinjaCharater 의 SetupPlayerInputComponent 에서 행해지던 모든 Controller의 역할을 NinjaBasePlayerController 로 이동.
* NinjaBasePlayerController 의경우 기존에 IMC에서 바로 받아오던 것을 DataAsset에 IMC를 받고 거기서 받아오는 것으로 변경 (추후 확장성을 위해서) (UNinjaPlayerInputConfigDataAsset* NinjaPlayerInputConfigDataAsset;)

	