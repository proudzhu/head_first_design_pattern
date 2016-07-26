/**
 * Created by proudzhu on 7/26/16.
 */
public class MiniDuckSimulator {
    public static void main(String[] args) {
        Duck mallerd = new MallardDuck();
        mallerd.performQuack();
        mallerd.performFly();

        Duck model = new ModelDuck();
        model.performFly();
        model.setFlyBehavior(new FlyRocketPowered());
        model.performFly();
    }
}
