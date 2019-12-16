#include <gazebo_model_reset_plugin.h>


namespace gazebo
{
  GZ_REGISTER_MODEL_PLUGIN(ResetPlugin)

  ResetPlugin::ResetPlugin(): ModelPlugin()
  {}

  void ResetPlugin::Load(physics::ModelPtr _parent, sdf::ElementPtr)
  {
    this->model = _parent;
    this->node = transport::NodePtr(new transport::Node());
    this->node->Init(this->model->GetWorld()->Name());
    std::string topicName = "~/" + this->model->GetName() + "/model_reset_plugin";
    this->sub = this->node->Subscribe(topicName,
                                      &ResetPlugin::OnMsg, this);
  }

  void ResetPlugin::OnMsg(ConstVector2dPtr &_msg)
  {
    if (_msg->x() == 1){
      this->model->Reset();
      this->model->ResetPhysicsStates();
    }
  }
}
